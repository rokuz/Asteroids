//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "gameObjectGraphics.h"

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "renderer.h"


#define BUFFER_OFFSET(i) ((char*)NULL + (i))
const int POSITION_SIZE = 3;
const int VERTEX_SIZE = POSITION_SIZE * sizeof(float);


namespace graphics
{

GameObjectGraphics::GameObjectGraphics() :
    m_vertexBuffer(0),
    m_vertexArray(0),
	m_trianglesCount(0)
{
	for (int i = 0; i < 4; i++) m_color[i] = 1.0f;
}

GameObjectGraphics::~GameObjectGraphics()
{
    destroy();
}
    
void GameObjectGraphics::init(const std::vector<triangle2d>& _triangles)
{
    // fill vertex buffer
    std::vector<float> buffer;
    buffer.resize(POSITION_SIZE * (int)_triangles.size() * 3);
    uint32 index = 0;
	m_trianglesCount = 0;
    for (size_t t = 0; t < _triangles.size(); t++)
    {
        if (_triangles[t].isDegenerate()) continue;
        
        buffer[index++] = _triangles[t].vertices[0].x;
        buffer[index++] = _triangles[t].vertices[0].y;
        buffer[index++] = 0.5f;
        
        buffer[index++] = _triangles[t].vertices[1].x;
        buffer[index++] = _triangles[t].vertices[1].y;
        buffer[index++] = 0.5f;
        
        buffer[index++] = _triangles[t].vertices[2].x;
        buffer[index++] = _triangles[t].vertices[2].y;
        buffer[index++] = 0.5f;
        
        m_trianglesCount++;
    }
    if (m_trianglesCount == 0) return;
    
    // create OGL primitives
    glGenVertexArraysOES(1, &m_vertexArray);
    glBindVertexArrayOES(m_vertexArray);
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, BUFFER_OFFSET(0));
    
	glBindVertexArrayOES(0);
}
    
void GameObjectGraphics::destroy()
{
    if (m_vertexBuffer != 0)
    {
        glDeleteBuffers(1, &m_vertexBuffer);
        m_vertexBuffer = 0;
    }
    
    if (m_vertexArray != 0)
    {
        glDeleteVertexArraysOES(1, &m_vertexArray);
        m_vertexArray = 0;
    }
}
    
void GameObjectGraphics::render()
{
    if (!isValid()) return;

	// bind vertex buffer
	glBindVertexArrayOES(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	// set shaders
	auto program = Renderer::instance().getProgram(SIMPLE_COLOR);
	glUseProgram(program->getProgram());
	glUniformMatrix4fv(program->getUniform(WVP_MATRIX), 1, false, &m_transform.m[0][0]);
	glUniform4fv(program->getUniform(COLOR_VECTOR), 1, m_color);

	// draw
    glDrawArrays(GL_TRIANGLES, 0, m_trianglesCount * 3);
}
    
bool GameObjectGraphics::isValid() const
{
    return m_vertexArray != 0 && m_vertexBuffer != 0;
}

void GameObjectGraphics::setTransform(const matrix& _transform)
{
	m_transform = _transform;
}

void GameObjectGraphics::setColor(const float _color[4])
{
	memcpy(m_color, _color, sizeof(m_color));
}


}
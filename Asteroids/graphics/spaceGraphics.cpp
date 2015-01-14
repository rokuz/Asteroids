//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "spaceGraphics.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

namespace graphics
{

SpaceGraphics::SpaceGraphics()
{
    
}

SpaceGraphics::~SpaceGraphics()
{
    destroy();
}
    
void SpaceGraphics::init(const vector2d& _size)
{
	m_projection.makeOrtho(_size.x, _size.y, 0, 1);
}
    
void SpaceGraphics::destroy()
{
}

void SpaceGraphics::render()
{
    if (!isValid()) return;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
    
bool SpaceGraphics::isValid() const
{
	return true;
}

const matrix& SpaceGraphics::getProjection() const
{
	return m_projection;
}
    
}
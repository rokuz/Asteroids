//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "gpuprogram.h"

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "../common/utils.h"
#include <list>

namespace graphics
{

GLint getOGLShaderType(ShaderType type)
{
	switch (type)
	{
	case graphics::VERTEX_SHADER:
		return GL_VERTEX_SHADER;

	case graphics::FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
    default:
        return -1;
	}
	return -1;
}

GpuProgram::GpuProgram() : 
	m_program(0)
{
	for (size_t i = 0; i < PARAMS_COUNT; i++)
		m_uniforms[i] = -1;

	m_shaders.resize(SHADERS_COUNT);
}

GpuProgram::~GpuProgram()
{
	destroy();
}

void GpuProgram::addShader(ShaderType _type, const std::string& _fileName)
{
	m_shaders[(int)_type] = _fileName;
}

bool GpuProgram::init()
{
	destroy();
	m_program = glCreateProgram();

	std::list<GLuint> compiledShaders;
	for (size_t shaderIndex = 0; shaderIndex < SHADERS_COUNT; shaderIndex++)
	{
		if (m_shaders[shaderIndex].empty()) continue;

		GLuint shader;
		if (!compileShader(&shader, getOGLShaderType((ShaderType)shaderIndex), m_shaders[shaderIndex]))
		{
			destroy();
			return false;
		}

		glAttachShader(m_program, shader);
		compiledShaders.push_back(shader);
	}

	if (compiledShaders.empty())
	{
		destroy();
		return false;
	}

	if (!linkProgram(m_program))
	{
		for (auto it = compiledShaders.begin(); it != compiledShaders.end(); ++it)
		{
			glDeleteShader(*it);
		}
		destroy();
		return false;
	}

	for (auto it = compiledShaders.begin(); it != compiledShaders.end(); ++it)
	{
		glDetachShader(m_program, *it);
		glDeleteShader(*it);
	}

	return true;
}

bool GpuProgram::isValid() const
{
	return m_program != 0;
}

void GpuProgram::destroy()
{
	if (m_program)
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}
}

bool GpuProgram::compileShader(uint32* _shader, uint32 _type, const std::string& _fileName)
{
	std::string sourceStr;
	utils::readFileToString(_fileName, sourceStr);
	if (sourceStr.empty())
	{
		return false;
	}

	GLint status;
	const GLchar *source = sourceStr.c_str();

	*_shader = glCreateShader(_type);
	glShaderSource(*_shader, 1, &source, NULL);
	glCompileShader(*_shader);

	glGetShaderiv(*_shader, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		glDeleteShader(*_shader);
		return false;
	}

	return true;
}

bool GpuProgram::linkProgram(uint32 _prog)
{
	GLint status;
	glLinkProgram(_prog);

	glGetProgramiv(_prog, GL_LINK_STATUS, &status);
	if (status == 0)
	{
		return false;
	}

	return true;
}

void GpuProgram::bindUniform(ParamType _param, const std::string& _name)
{
	if (!isValid()) return;
	
	m_uniforms[(int)_param] = glGetUniformLocation(m_program, _name.c_str());
}

int GpuProgram::getUniform(ParamType _param) const
{
	return m_uniforms[(int)_param];
}

uint32 GpuProgram::getProgram() const
{
	return m_program;
}

}
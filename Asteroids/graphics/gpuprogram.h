//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once
#include "../common/types.h"
#include "../math/matrix.h"
#include <string>
#include <vector>

namespace graphics
{

enum ShaderType
{
	VERTEX_SHADER = 0,
	FRAGMENT_SHADER,
	SHADERS_COUNT
};

enum ParamType
{
	WVP_MATRIX = 0,
	COLOR_VECTOR,
	PARAMS_COUNT
};

class GpuProgram
{
public:
	GpuProgram();
	virtual ~GpuProgram();

	void addShader(ShaderType _type, const std::string& _fileName);
	bool init();
	bool isValid() const;
	void destroy();

	uint32 getProgram() const;
	void bindUniform(ParamType _param, const std::string& _name);
	int getUniform(ParamType _param) const;

private:
	uint32 m_program;
	int m_uniforms[PARAMS_COUNT];
	std::vector<std::string> m_shaders;
	
	bool compileShader(uint32* _shader, uint32 _type, const std::string& _fileName);
	bool linkProgram(uint32 _prog);
};

}
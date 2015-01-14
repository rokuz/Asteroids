//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "renderer.h"

std::string getResourceName(const char* _resource, const char* _ext)
{
    std::string result;
    @autoreleasepool
    {
        NSString* res = [NSString stringWithUTF8String:_resource];
        NSString* ext = [NSString stringWithUTF8String:_ext];
        NSString* resourcePathname = [[NSBundle mainBundle] pathForResource:res ofType:ext];
        result = [resourcePathname UTF8String];
    }
    return result;
}

namespace graphics
{

Renderer& Renderer::instance()
{
	static Renderer rendererInstance;
	return rendererInstance;
}

Renderer::Renderer()
{
	m_programs.resize((int)MATERIALS_COUNT);
}

Renderer::~Renderer()
{
	destroy();
}

bool Renderer::init()
{
	m_programs[(int)SIMPLE_COLOR].reset(new GpuProgram());
	m_programs[(int)SIMPLE_COLOR]->addShader(VERTEX_SHADER, getResourceName("simple_color", "vsh"));
	m_programs[(int)SIMPLE_COLOR]->addShader(FRAGMENT_SHADER, getResourceName("simple_color", "fsh"));
	if (!m_programs[(int)SIMPLE_COLOR]->init())
	{
		return false;
	}
	m_programs[(int)SIMPLE_COLOR]->bindUniform(WVP_MATRIX, "modelViewProjectionMatrix");
	m_programs[(int)SIMPLE_COLOR]->bindUniform(COLOR_VECTOR, "diffuseColor");

	return true;
}

void Renderer::destroy()
{
	m_programs.clear();
}

std::shared_ptr<GpuProgram> Renderer::getProgram(MaterialType _material) const
{
	return m_programs[(int)_material];
}

}
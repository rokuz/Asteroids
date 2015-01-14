//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include <memory>
#include <vector>
#include "gpuprogram.h"

namespace graphics
{

enum MaterialType
{
	SIMPLE_COLOR = 0,
	MATERIALS_COUNT
};

class Renderer
{
public:
	static Renderer& instance();

	bool init();
	void destroy();

	std::shared_ptr<GpuProgram> getProgram(MaterialType _material) const;

private:
	Renderer();
	~Renderer();

	std::vector<std::shared_ptr<GpuProgram> > m_programs;
};

}
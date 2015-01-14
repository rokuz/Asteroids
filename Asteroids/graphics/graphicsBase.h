//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

namespace graphics
{

class GraphicsBase
{
public:
	virtual ~GraphicsBase(){}

	virtual void update(float _dt) {}
	virtual void render() {}
};

}
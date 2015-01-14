//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include "../common/types.h"
#include "../math/matrix.h"
#include "../graphics/graphicsBase.h"

namespace graphics
{
    
class SpaceGraphics : public GraphicsBase
{
public:
	SpaceGraphics();
	virtual ~SpaceGraphics();
    
    void init(const vector2d& _size);
	void destroy();
    bool isValid() const;

	const matrix& getProjection() const;

	virtual void render();
    
private:
	matrix m_projection;
};
    
}
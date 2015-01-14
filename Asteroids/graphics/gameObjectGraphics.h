//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include "../common/types.h"
#include "../math/triangle2D.h"
#include "../math/matrix.h"
#include "../graphics/graphicsBase.h"

namespace graphics
{
    
class GameObjectGraphics : public GraphicsBase
{
public:
    GameObjectGraphics();
    ~GameObjectGraphics();
    
    void init(const std::vector<triangle2d>& _triangles);
    void destroy();
	bool isValid() const;

    virtual void render();
    
	void setTransform(const matrix& _transform);
    void setColor(const float _color[4]);

private:
    uint32 m_vertexBuffer;
    uint32 m_vertexArray;
	matrix m_transform;
	uint32 m_trianglesCount;
	float m_color[4];
};
    
}
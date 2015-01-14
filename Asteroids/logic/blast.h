//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include <memory>
#include "../math/matrix.h"

namespace graphics
{
	class GameObjectGraphics;
}

namespace physics
{
	class BlastPhysics;
}

namespace logic
{

class Blast
{
public:
	Blast();
	~Blast();

	bool create(const vector2d& _position);
	void setTransformToGameField(const matrix& _transform);
	void setPosition(const vector2d& _position);

	std::shared_ptr<physics::BlastPhysics> getPhysics() const;

	void update(float _dt);
	void render();

private:
	matrix m_fieldTransform;

	std::shared_ptr<graphics::GameObjectGraphics> m_graphics;
	std::shared_ptr<physics::BlastPhysics> m_physics;
};

}
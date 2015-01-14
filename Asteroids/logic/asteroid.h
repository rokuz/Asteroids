//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include <memory>
#include <functional>
#include "../math/matrix.h"

namespace graphics
{
	class GameObjectGraphics;
}

namespace physics
{
	class AsteroidPhysics;
}

namespace logic
{

enum AsteroidType
{
	BIG_ASTEROID,
	SMALL_ASTEROID
};

class Asteroid;
typedef std::function<void(Asteroid*)> AsteroidHandler;

class Asteroid
{
public:
	Asteroid();
	~Asteroid();

	bool create(AsteroidType _type, uint32 _health, float _radius, const vector2d& _position);
	void setCriticalDamageHandler(AsteroidHandler _handler);
	void setTransformToGameField(const matrix& _transform);
	void setPosition(const vector2d& _position);
	void setHealth(uint32 _health);
	void damage(int _damage);

	std::shared_ptr<physics::AsteroidPhysics> getPhysics() const;
	AsteroidType getType() const;

	void update(float _dt);
	void render();

private:
	AsteroidType m_type;
	uint32 m_health;
	AsteroidHandler m_onCriticalDamage;
	matrix m_fieldTransform;

	std::shared_ptr<graphics::GameObjectGraphics> m_graphics;
	std::shared_ptr<physics::AsteroidPhysics> m_physics;
};

}
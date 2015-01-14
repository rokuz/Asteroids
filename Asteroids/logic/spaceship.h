//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include <memory>
#include <functional>
#include <vector>
#include "../math/matrix.h"

namespace graphics
{
	class GameObjectGraphics;
}

namespace physics
{
	class Body;
}

namespace logic
{

class Spaceship;
typedef std::function<void(Spaceship*)> SpaceshipHandler;

class Spaceship
{
public:
	Spaceship();
	~Spaceship();

	bool create(uint32 _health, const vector2d& _position, const vector2d& _size, const vector2d& _fieldSize);
	void setTransformToGameField(const matrix& _transform);
	void setPosition(const vector2d& _position);
	void setHealth(uint32 _health);
	void setCriticalDamageHandler(SpaceshipHandler _handler);

	std::shared_ptr<physics::Body> getPhysics() const;
    float getHealth() const;

	void fire(bool _on);
	std::vector<vector2d> getBlasts(float _dt);
	void move(float _d);

	void damage(int _damage);

	void update(float _dt);
	void render();

private:
	matrix m_fieldTransform;
	vector2d m_fieldSize;
	vector2d m_size;

	uint32 m_health;
	SpaceshipHandler m_onCriticalDamage;

	bool m_isShooting;
	float m_lastShotTime;

	std::shared_ptr<graphics::GameObjectGraphics> m_graphics;
	std::shared_ptr<physics::Body> m_physics;
};

}
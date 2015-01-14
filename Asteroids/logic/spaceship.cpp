//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "spaceship.h"
#include "gameParams.h"
#include "../graphics/gameObjectGraphics.h"
#include "../physics/body.h"

namespace logic
{

Spaceship::Spaceship() :
	m_isShooting(false),
	m_lastShotTime(0),
	m_health(0)
{
}

Spaceship::~Spaceship()
{
}

bool Spaceship::create(uint32 _health, const vector2d & _position, const vector2d& _size, const vector2d& _fieldSize)
{
	m_health = _health;
	m_size = _size;
	m_fieldSize = _fieldSize;

	m_physics.reset(new physics::Body());
	std::vector<triangle2d> t;
	t.resize(1);
	t[0].vertices[0] = vector2d(-_size.x * 0.5f, 0.0f);
	t[0].vertices[1] = vector2d(0.0f, _size.y);
	t[0].vertices[2] = vector2d(_size.x * 0.5f, 0.0f);
	m_physics->setTriangles(t);
	m_physics->setPosition(_position);

	m_graphics.reset(new graphics::GameObjectGraphics());
	m_graphics->init(t);
	m_graphics->setColor(SPACESHIP_COLOR);
	if (!m_graphics->isValid()) return false;

	return true;
}

void Spaceship::setTransformToGameField(const matrix& _transform)
{
	m_fieldTransform = _transform;
}

void Spaceship::setPosition(const vector2d& _position)
{
	m_physics->setPosition(_position);
}

void Spaceship::setHealth(uint32 _health)
{
	m_health = _health;
}

std::shared_ptr<physics::Body> Spaceship::getPhysics() const
{
	return m_physics;
}
    
float Spaceship::getHealth() const
{
    return m_health;
}

void Spaceship::fire(bool _on)
{
	m_isShooting = _on;
	if (!m_isShooting) m_lastShotTime = 0;
}

std::vector<vector2d> Spaceship::getBlasts(float _dt)
{
	if (!m_isShooting) return std::vector<vector2d>();
	
	bool generate = (fabs(m_lastShotTime) < 1e-5);
	m_lastShotTime += _dt;
	if (m_lastShotTime >= SPACESHIP_SHOT_TIME)
	{
		m_lastShotTime -= SPACESHIP_SHOT_TIME * (int)(m_lastShotTime / SPACESHIP_SHOT_TIME);
		generate = true;
	}

	if (generate)
	{
		auto p = m_physics->getTransform().position();
		std::vector<vector2d> result;
		result.resize(2);
		result[0] = vector2d(-0.5f * m_size.x + p.x, p.y);
		result[1] = vector2d(0.5f * m_size.x + p.x, p.y);

		return result;
	}

	return std::vector<vector2d>();
}

void Spaceship::move(float _d)
{
	vector2d p = m_physics->getTransform().position();
	p.x += _d;
    
	float border = 0.5f * (m_fieldSize.x - m_size.x);
	if (p.x > border) p.x = border;
    
    border = -0.5f * (m_fieldSize.x - m_size.x);
	if (p.x < border) p.x = border;
    
	m_physics->setPosition(p);
}

void Spaceship::damage(int _damage)
{
	int health = (int)m_health;
	health -= _damage;
	if (health < 0) health = 0;
	m_health = health;

	if (m_health == 0 && m_onCriticalDamage != nullptr) m_onCriticalDamage(this);
}

void Spaceship::setCriticalDamageHandler(SpaceshipHandler _handler)
{
	m_onCriticalDamage = _handler;
}

void Spaceship::update(float _dt)
{
	m_physics->update(_dt);

	// setup transform from physics
	matrix t = m_physics->getTransform();
	t *= m_fieldTransform;
	m_graphics->setTransform(t);

	m_graphics->update(_dt);
}

void Spaceship::render()
{
	m_graphics->render();
}

}
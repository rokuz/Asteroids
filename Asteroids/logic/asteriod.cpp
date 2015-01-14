//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "asteroid.h"
#include "gameParams.h"
#include "../graphics/gameObjectGraphics.h"
#include "../physics/asteroidPhysics.h"

namespace logic
{

Asteroid::Asteroid() :
	m_health(0)
{
}

Asteroid::~Asteroid()
{
}

bool Asteroid::create(AsteroidType _type, uint32 _health, float _radius, const vector2d & _position)
{
	m_type = _type;
	m_health = _health;

	m_physics.reset(new physics::AsteroidPhysics(_radius, 
												 ASTEROID_VELOCITY, 
												 ASTEROID_ANGULAR_VELOCITY, 
												 _position, 
												 vector2d(0.0f, -1.0f)));

	m_graphics.reset(new graphics::GameObjectGraphics());
	m_graphics->init(m_physics->getTriangles());
	m_graphics->setColor(ASTEROID_COLOR);
	if (!m_graphics->isValid()) return false;

	return true;
}

void Asteroid::setCriticalDamageHandler(AsteroidHandler _handler)
{
	m_onCriticalDamage = _handler;
}

void Asteroid::setTransformToGameField(const matrix& _transform)
{
	m_fieldTransform = _transform;
}

void Asteroid::setPosition(const vector2d& _position)
{
	m_physics->setPosition(_position);
}

void Asteroid::setHealth(uint32 _health)
{
	m_health = _health;
}

void Asteroid::damage(int _damage)
{
	int health = (int)m_health;
	health -= _damage;
	if (health < 0) health = 0;
	m_health = health;

	if (m_health == 0 && m_onCriticalDamage != nullptr) m_onCriticalDamage(this);
}

std::shared_ptr<physics::AsteroidPhysics> Asteroid::getPhysics() const
{
	return m_physics;
}

AsteroidType Asteroid::getType() const
{
	return m_type;
}

void Asteroid::update(float _dt)
{
	m_physics->update(_dt);

	// setup transform from physics
	matrix t = m_physics->getTransform();
	t *= m_fieldTransform;
	m_graphics->setTransform(t);

	m_graphics->update(_dt);
}

void Asteroid::render()
{
	m_graphics->render();
}

}
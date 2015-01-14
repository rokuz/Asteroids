//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "blast.h"
#include "gameParams.h"
#include "../graphics/gameObjectGraphics.h"
#include "../physics/blastPhysics.h"


namespace logic
{

Blast::Blast()
{
}

Blast::~Blast()
{
}

bool Blast::create(const vector2d & _position)
{
	m_physics.reset(new physics::BlastPhysics(BLAST_LENGTH, 
											  BLAST_VELOCITY, 
											  _position, 
											  vector2d(0.0f, 1.0f)));

	m_graphics.reset(new graphics::GameObjectGraphics());
	m_graphics->init(m_physics->getTriangles());
	m_graphics->setColor(BLAST_COLOR);
	if (!m_graphics->isValid()) return false;

	return true;
}

void Blast::setTransformToGameField(const matrix& _transform)
{
	m_fieldTransform = _transform;
}

void Blast::setPosition(const vector2d& _position)
{
	m_physics->setPosition(_position);
}

std::shared_ptr<physics::BlastPhysics> Blast::getPhysics() const
{
	return m_physics;
}

void Blast::update(float _dt)
{
	m_physics->update(_dt);

	// setup transform from physics
	matrix t = m_physics->getTransform();
	t *= m_fieldTransform;
	m_graphics->setTransform(t);

	m_graphics->update(_dt);
}

void Blast::render()
{
	m_graphics->render();
}

}
//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include "body.h"
#include <vector>

namespace physics
{

class AsteroidPhysics : public Body
{
public:
	AsteroidPhysics(float _radius, float _velocity, float _angularVelocity,
					const vector2d& _position, const vector2d& _direction);
	virtual ~AsteroidPhysics();

	const std::vector<vector2d> & getPoints() const;
	const std::vector<bool> & intersectionFilter() const;
	float getRadius() const;

private:
	std::vector<vector2d> m_points;
	float m_radius;

	void generate(float _radius);
};

}
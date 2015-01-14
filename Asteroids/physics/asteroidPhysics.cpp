//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "asteroidPhysics.h"

#include "../common/utils.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace physics
{

const int GEN_MIN_POINTS = 8;
const int GEN_MAX_POINTS = 16;
const float GEN_MIN_RADIUS = 0.5f;

const std::vector<bool> & asteroidIntersectionFilter()
{
	static std::vector<bool> v;
	if (v.empty())
	{
		// check for intersection only external edges
		v.resize(3);
		v[0] = false; v[1] = true; v[2] = false;
	}
	return v;
}

AsteroidPhysics::AsteroidPhysics(float _radius, float _velocity, float _angularVelocity,
								 const vector2d& _position, const vector2d& _direction)
{
	m_radius = _radius;
	m_position = _position;
	m_velocityDirection = _direction;
	m_velocity = _velocity;
	m_angularVelocity = _angularVelocity;

	generate(_radius);

	// set initial state
	update(0);
}

AsteroidPhysics::~AsteroidPhysics()
{
}

void AsteroidPhysics::generate(float _radius)
{
	int points = utils::random(GEN_MIN_POINTS, GEN_MAX_POINTS);
	m_points.reserve(points);

	float sector = 2.0f * (float)M_PI / points;
	for (int i = 0; i < points; i++)
	{
		// calculate a vertex of asteroid in polar coordinates
		float ang = utils::random(sector * i, sector * (i + 1));
		float r = _radius * utils::random(GEN_MIN_RADIUS, 1.0f);

		m_points.push_back(vector2d(cos(ang) * r, sin(ang) * r));
	}

	m_triangles.reserve(m_points.size());
    m_transformedTriangles.resize(m_points.size());
	for (size_t i = 0; i < m_points.size(); i++)
	{
		size_t index = i;
		size_t next = (i != m_points.size() - 1) ? i + 1 : 0;
		m_triangles.push_back(triangle2d(vector2d(), m_points[index], m_points[next]));
	}
}

const std::vector<vector2d> & AsteroidPhysics::getPoints() const
{
	return m_points;
}

const std::vector<bool> & AsteroidPhysics::intersectionFilter() const
{
	return asteroidIntersectionFilter();
}

float AsteroidPhysics::getRadius() const
{
	return m_radius;
}

}
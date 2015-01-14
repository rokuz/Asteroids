//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "blastPhysics.h"

#include "../common/utils.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace physics
{

const float BLAST_WIDTH = 0.1f;
    
const std::vector<bool> & blastIntersectionFilter()
{
    static std::vector<bool> v;
    if (v.empty())
    {
        v.resize(3);
        v[0] = true; v[1] = false; v[2] = false;
    }
    return v;
}

BlastPhysics::BlastPhysics(float _length, float _velocity, const vector2d& _position, const vector2d& _direction)
{
	m_length = _length;
	m_position = _position;
	m_velocityDirection = _direction;
	m_velocity = _velocity;

	generate(_length);

	// set initial state
	update(0);
}

BlastPhysics::~BlastPhysics()
{
}

void BlastPhysics::generate(float _length)
{
	m_points.resize(4);
	m_points[0] = vector2d(-0.5f * BLAST_WIDTH, 0.0f);
	m_points[1] = vector2d(-0.5f * BLAST_WIDTH, _length);
	m_points[2] = vector2d(0.5f * BLAST_WIDTH, _length);
	m_points[3] = vector2d(0.5f * BLAST_WIDTH, 0.0f);

	m_triangles.reserve(2);
	m_transformedTriangles.resize(2);

	m_triangles.push_back(triangle2d(m_points[0], m_points[1], m_points[2]));
	m_triangles.push_back(triangle2d(m_points[0], m_points[2], m_points[3]));
}

const std::vector<vector2d> & BlastPhysics::getPoints() const
{
	return m_points;
}

float BlastPhysics::getLength() const
{
	return m_length;
}
    
const std::vector<bool> & BlastPhysics::intersectionFilter() const
{
    return blastIntersectionFilter();
}

bool BlastPhysics::intersects(const Body& _body) const
{
	// collision detection by bounding spheres
	vector2d c1 = m_boundingBox.center();
	float r1 = m_boundingBox.radius();
	vector2d c2 = _body.getBoundingBox().center();
	float r2 = _body.getBoundingBox().radius();
	float d = (c2 - c1).length();
	if (d > r1 + r2) return false;
    
	// collision detection by triangles intersection
	for (size_t j = 0; j < _body.getTransformedTriangles().size(); j++)
	{
		if (m_transformedTriangles[0].intersects(_body.getTransformedTriangles()[j], intersectionFilter(), _body.intersectionFilter()))
		{
			return true;
		}
	}
	return false;
}

}
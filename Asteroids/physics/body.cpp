//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "body.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace physics
{

Body::Body() :
	m_angularVelocity(0.0f),
	m_velocity(0.0f),
	m_angle(0.0f)
{
	// set initial state
	update(0);
}

Body::~Body()
{
}

void Body::setPosition(const vector2d& _position)
{
	m_position = _position;
	updateTransform();
}

void Body::setTriangles(const std::vector<triangle2d>& _triangles)
{
	m_triangles = _triangles;
	m_transformedTriangles.resize(m_triangles.size());
}

void Body::update(float _dt)
{
	// calculate motion
	m_position = m_position + m_velocityDirection * m_velocity * _dt;
	m_angle += m_angularVelocity * _dt;
	const float TWOPI = 2.0f * (float)M_PI;
	if (m_angle > TWOPI)
	{
		m_angle = m_angle - TWOPI * (int)(m_angle / TWOPI);
	}

	updateTransform();
}

const std::vector<bool> & Body::intersectionFilter() const
{
	static std::vector<bool> v;
	return v;
}
    
const std::vector<triangle2d>& Body::getTriangles() const
{
    return m_triangles;
}

const std::vector<triangle2d>& Body::getTransformedTriangles() const
{
	return m_transformedTriangles;
}

const bbox& Body::getBoundingBox() const
{
	return m_boundingBox;
}

const matrix& Body::getTransform() const
{
	return m_transform;
}

bool Body::intersects(const Body& _body) const
{
	// collision detection by bounding spheres
	vector2d c1 = m_boundingBox.center();
	float r1 = m_boundingBox.radius();
	vector2d c2 = _body.getBoundingBox().center();
	float r2 = _body.getBoundingBox().radius();
	float d = (c2 - c1).length();
	if (d > r1 + r2) return false;

	// collision detection by triangles intersection
	for (size_t i = 0; i < m_transformedTriangles.size(); i++)
	{
		for (size_t j = 0; j < _body.m_transformedTriangles.size(); j++)
		{
			if (m_transformedTriangles[i].intersects(_body.m_transformedTriangles[j], 
													 intersectionFilter(),
													 _body.intersectionFilter()))
			{
				return true;
			}
		}
	}
	return false;
}

void Body::updateTransform()
{
	m_transform.makeIdentity();
	m_transform.rotateZ(m_angle);
	m_transform.setTranslation(m_position);

	m_boundingBox = bbox();
	for (size_t i = 0; i < m_triangles.size(); i++)
	{
		m_transformedTriangles[i] = m_triangles[i].transform(m_transform);

		// recompute bounding box
		vector2d mn = m_transformedTriangles[i].getMin();
		vector2d mx = m_transformedTriangles[i].getMax();
		m_boundingBox.extend(mn);
		m_boundingBox.extend(mx);
	}
}

}
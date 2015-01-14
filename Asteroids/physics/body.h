//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include "../math/triangle2D.h"
#include "../math/matrix.h"
#include "../math/bbox.h"

#include <vector>

namespace physics
{

class Body
{
public:
	Body();
	virtual ~Body();
	virtual void update(float _dt);
	virtual const std::vector<bool> & intersectionFilter() const;
	virtual bool intersects(const Body& _body) const;

    const std::vector<triangle2d>& getTriangles() const;
	const std::vector<triangle2d>& getTransformedTriangles() const;
	const matrix& getTransform() const;
	const bbox& getBoundingBox() const;

	void setPosition(const vector2d& _position);
	void setTriangles(const std::vector<triangle2d>& _triangles);

protected:
	float m_angularVelocity;
	float m_angle;
	float m_velocity;
	vector2d m_velocityDirection;
	vector2d m_position;

	std::vector<triangle2d> m_triangles;

	matrix m_transform;
	std::vector<triangle2d> m_transformedTriangles;
	bbox m_boundingBox;

	void updateTransform();
};

}
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

class BlastPhysics : public Body
{
public:
	BlastPhysics(float _length, float _velocity, const vector2d& _position, const vector2d& _direction);
	virtual ~BlastPhysics();
	virtual bool intersects(const Body& _body) const;
    const std::vector<bool> & intersectionFilter() const;

	const std::vector<vector2d> & getPoints() const;
	float getLength() const;

private:
	std::vector<vector2d> m_points;
	float m_length;

	void generate(float _length);
};

}
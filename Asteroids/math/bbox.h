//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once
#include "vector2D.h"

namespace math
{

const float INF = 1000000.0f;

struct Bbox
{
public:
	Bbox() : boxMin(vector2d(INF, INF)), boxMax(vector2d(-INF, -INF)) {}
	Bbox(const vector2d& _min, const vector2d& _max) : boxMin(_min), boxMax(_max) {}
	Bbox(const Bbox& _v) : boxMin(_v.boxMin), boxMax(_v.boxMax) {}

	void extend(const vector2d& _v)
	{
		if (_v.x < boxMin.x) boxMin.x = _v.x;
		if (_v.y < boxMin.y) boxMin.y = _v.y;
		if (_v.x > boxMax.x) boxMax.x = _v.x;
		if (_v.y > boxMax.y) boxMax.y = _v.y;
	}

	vector2d size() const
	{
		return vector2d(boxMax.x - boxMin.x, boxMax.y - boxMin.y);
	}

	vector2d center() const
	{
		return vector2d(0.5f * (boxMin.x + boxMax.x), 0.5f * (boxMin.y + boxMax.y));
	}

	float radius() const
	{
		vector2d halfSize = size() * 0.5f;
		return sqrt(halfSize.x * halfSize.x + halfSize.y * halfSize.y);
	}

	vector2d boxMin;
	vector2d boxMax;
};

}
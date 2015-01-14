//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once
#include "vector2D.h"
#include <algorithm>
#undef min
#undef max

namespace math
{

struct Edge2D
{
	Edge2D(){}
	Edge2D(const vector2d& _p1, const vector2d& _p2)
	{
		points[0] = _p1;
		points[1] = _p2;
	}

	bool isDegenerate() const
	{
		return (points[1] - points[0]).isZero();
	}

	bool intersects(const Edge2D& _t) const
	{
		// implementation from here http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

		float s10_x = points[1].x - points[0].x;
		float s10_y = points[1].y - points[0].y;
		float s32_x = _t.points[1].x - _t.points[0].x;
		float s32_y = _t.points[1].y - _t.points[0].y;

		float denom = s10_x * s32_y - s32_x * s10_y;
		if (denom == 0)
			return false;

		bool denomPositive = denom > 0;

		float s02_x = points[0].x - _t.points[0].x;
		float s02_y = points[0].y - _t.points[0].y;

		float s_numer = s10_x * s02_y - s10_y * s02_x;
		if ((s_numer < 0) == denomPositive)
			return false;

		float t_numer = s32_x * s02_y - s32_y * s02_x;
		if ((t_numer < 0) == denomPositive)
			return false;

		if (((s_numer > denom) == denomPositive) || ((t_numer > denom) == denomPositive))
			return false;

		return true;
	}

	vector2d points[2];
};

}
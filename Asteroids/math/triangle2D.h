//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once
#include "edge2D.h"
#include "matrix.h"
#include <vector>

namespace math
{

struct Triangle2D
{
	Triangle2D(){}
	Triangle2D(const vector2d& _v1, const vector2d& _v2, const vector2d& _v3)
	{
		vertices[0] = _v1;
		vertices[1] = _v2;
		vertices[2] = _v3;
	}

	Edge2D getEgde(uint32 _index) const
	{
		if (_index >= 3) return Edge2D();
		return Edge2D(vertices[_index], vertices[(_index + 1) % 3]);
	}

	Triangle2D transform(const Matrix& _matrix) const
	{
		return Triangle2D(_matrix.transform(vertices[0]),
						  _matrix.transform(vertices[1]),
						  _matrix.transform(vertices[2]));
	}

	bool isDegenerate() const
	{
		for (uint32 i = 0; i < 3; i++)
		{
			if (getEgde(i).isDegenerate()) return true;
		}
		return false;
	}

	bool intersects(const Triangle2D& _t, 
					const std::vector<bool>& filter = std::vector<bool>(),
					const std::vector<bool>& filter2 = std::vector<bool>()) const
	{
		for (uint32 i = 0; i < 3; i++)
		{
			if (filter.size() == 3 && !filter[i]) continue;
			for (uint32 j = 0; j < 3; j++)
			{
				if (filter2.size() == 3 && !filter2[j]) continue;
				if (getEgde(i).intersects(_t.getEgde(j))) return true;
			}
		}
		return false;
	}

	vector2d getMin()
	{
		vector2d m = vertices[0];
		for (int i = 1; i < 3; i++)
		{
			if (vertices[i].x < m.x) m.x = vertices[i].x;
			if (vertices[i].y < m.y) m.y = vertices[i].y;
		}
		return m;
	}

	vector2d getMax()
	{
		vector2d m = vertices[0];
		for (int i = 1; i < 3; i++)
		{
			if (vertices[i].x > m.x) m.x = vertices[i].x;
			if (vertices[i].y > m.y) m.y = vertices[i].y;
		}
		return m;
	}

	vector2d vertices[3];
};

}
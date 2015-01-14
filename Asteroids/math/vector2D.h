//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once
#include <math.h>
#include "../common/types.h"

namespace math
{

const double EPS = 1e-5;

template<typename T>
struct Vector2D
{
public:
	typedef T NumberType;

	Vector2D() : x(0), y(0) {}
	Vector2D(T _x, T _y) : x(_x), y(_y) {}
	Vector2D(const Vector2D& _v) : x(_v.x), y(_v.y) {}

	Vector2D operator+(const Vector2D& _v) const
	{
		Vector2D result;
		result.x = x + _v.x;
		result.y = y + _v.y;
		return result;
	}

	Vector2D operator-(const Vector2D& _v) const
	{
		Vector2D result;
		result.x = x - _v.x;
		result.y = y - _v.y;
		return result;
	}

	Vector2D operator*(T _scalar) const
	{
		Vector2D result;
		result.x = x * _scalar;
		result.y = y * _scalar;
		return result;
	}

	Vector2D& operator=(const Vector2D& _v)
	{
		if (&_v == this) return *this;
		x = _v.x;
		y = _v.y;
		return *this;
	}

	void normalize()
	{
		if (isZero()) return;	
		T d = length();
		x /= d;
		y /= d;
	}

	T length() const
	{
		return sqrt(x * x + y * y);
	}

	bool isZero() const
	{
		T d = x * x + y * y;
		if (d < (T)EPS) return true;
		return false;
	}

	T x;
	T y;
};

}
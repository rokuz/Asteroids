//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

typedef unsigned int uint32;


namespace math
{
	template<typename T> struct Vector2D;
	struct Triangle2D;
	struct Edge2D;
	struct Bbox;
	class Matrix;
}
typedef math::Vector2D<float> vector2d;
typedef math::Triangle2D triangle2d;
typedef math::Triangle2D edge2d;
typedef math::Matrix matrix;
typedef math::Bbox bbox;
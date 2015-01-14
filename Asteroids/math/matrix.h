//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once
#include "vector2D.h"
#include <memory.h>
#include <algorithm>

namespace math
{

static float matrix_ident[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

#define M11 m[0][0]
#define M12 m[0][1]
#define M13 m[0][2]
#define M14 m[0][3]
#define M21 m[1][0]
#define M22 m[1][1]
#define M23 m[1][2]
#define M24 m[1][3]
#define M31 m[2][0]
#define M32 m[2][1]
#define M33 m[2][2]
#define M34 m[2][3]
#define M41 m[3][0]
#define M42 m[3][1]
#define M43 m[3][2]
#define M44 m[3][3]

class Matrix
{

public:
    Matrix()
	{
		memcpy(&(m[0][0]), matrix_ident, sizeof(matrix_ident));
	}

    Matrix(const Matrix& _m)
	{
		memcpy(m, &(_m.m[0][0]), 16 * sizeof(float));
	}

    Matrix(float _m11, float _m12, float _m13, float _m14,
           float _m21, float _m22, float _m23, float _m24,
           float _m31, float _m32, float _m33, float _m34,
           float _m41, float _m42, float _m43, float _m44)
	{
		M11 = _m11; M12 = _m12; M13 = _m13; M14 = _m14;
		M21 = _m21; M22 = _m22; M23 = _m23; M24 = _m24;
		M31 = _m31; M32 = _m32; M33 = _m33; M34 = _m34;
		M41 = _m41; M42 = _m42; M43 = _m43; M44 = _m44;
	}

	void set(float _m11, float _m12, float _m13, float _m14,
			 float _m21, float _m22, float _m23, float _m24,
			 float _m31, float _m32, float _m33, float _m34,
			 float _m41, float _m42, float _m43, float _m44)
	{
		M11 = _m11; M12 = _m12; M13 = _m13; M14 = _m14;
		M21 = _m21; M22 = _m22; M23 = _m23; M24 = _m24;
		M31 = _m31; M32 = _m32; M33 = _m33; M34 = _m34;
		M41 = _m41; M42 = _m42; M43 = _m43; M44 = _m44;
	}

    void makeIdentity()
	{
		memcpy(&(m[0][0]), matrix_ident, sizeof(matrix_ident));
	}

    void transpose()
	{
		std::swap(M12, M21);
		std::swap(M13, M31);
		std::swap(M14, M41);
		std::swap(M23, M32);
		std::swap(M24, M42);
		std::swap(M34, M43);
	}

    float determinant() const
	{
		return  (M11 * M22 - M12 * M21) * (M33 * M44 - M34 * M43)
			   -(M11 * M23 - M13 * M21) * (M32 * M44 - M34 * M42)
			   +(M11 * M24 - M14 * M21) * (M32 * M43 - M33 * M42)
			   +(M12 * M23 - M13 * M22) * (M31 * M44 - M34 * M41)
			   -(M12 * M24 - M14 * M22) * (M31 * M43 - M33 * M41)
			   +(M13 * M24 - M14 * M23) * (M31 * M42 - M32 * M41);
	}

    void invert()
	{
		float s = determinant();
		if (fabs(s) < EPS) return;

		s = 1.0f / s;
		set(s*(M22*(M33*M44 - M34*M43) + M23*(M34*M42 - M32*M44) + M24*(M32*M43 - M33*M42)),
			s*(M32*(M13*M44 - M14*M43) + M33*(M14*M42 - M12*M44) + M34*(M12*M43 - M13*M42)),
			s*(M42*(M13*M24 - M14*M23) + M43*(M14*M22 - M12*M24) + M44*(M12*M23 - M13*M22)),
			s*(M12*(M24*M33 - M23*M34) + M13*(M22*M34 - M24*M32) + M14*(M23*M32 - M22*M33)),
			s*(M23*(M31*M44 - M34*M41) + M24*(M33*M41 - M31*M43) + M21*(M34*M43 - M33*M44)),
			s*(M33*(M11*M44 - M14*M41) + M34*(M13*M41 - M11*M43) + M31*(M14*M43 - M13*M44)),
			s*(M43*(M11*M24 - M14*M21) + M44*(M13*M21 - M11*M23) + M41*(M14*M23 - M13*M24)),
			s*(M13*(M24*M31 - M21*M34) + M14*(M21*M33 - M23*M31) + M11*(M23*M34 - M24*M33)),
			s*(M24*(M31*M42 - M32*M41) + M21*(M32*M44 - M34*M42) + M22*(M34*M41 - M31*M44)),
			s*(M34*(M11*M42 - M12*M41) + M31*(M12*M44 - M14*M42) + M32*(M14*M41 - M11*M44)),
			s*(M44*(M11*M22 - M12*M21) + M41*(M12*M24 - M14*M22) + M42*(M14*M21 - M11*M24)),
			s*(M14*(M22*M31 - M21*M32) + M11*(M24*M32 - M22*M34) + M12*(M21*M34 - M24*M31)),
			s*(M21*(M33*M42 - M32*M43) + M22*(M31*M43 - M33*M41) + M23*(M32*M41 - M31*M42)),
			s*(M31*(M13*M42 - M12*M43) + M32*(M11*M43 - M13*M41) + M33*(M12*M41 - M11*M42)),
			s*(M41*(M13*M22 - M12*M23) + M42*(M11*M23 - M13*M21) + M43*(M12*M21 - M11*M22)),
			s*(M11*(M22*M33 - M23*M32) + M12*(M23*M31 - M21*M33) + M13*(M21*M32 - M22*M31)));
	}

    void invert3x3()
	{
		float s = determinant();
		if (fabs(s) < EPS) return;

		s = 1.0f / s;
		set(s * ((M22 * M33) - (M23 * M32)),
			s * ((M32 * M13) - (M33 * M12)),
			s * ((M12 * M23) - (M13 * M22)),
			0.0f,
			s * ((M23 * M31) - (M21 * M33)),
			s * ((M33 * M11) - (M31 * M13)),
			s * ((M13 * M21) - (M11 * M23)),
			0.0f,
			s * ((M21 * M32) - (M22 * M31)),
			s * ((M31 * M12) - (M32 * M11)),
			s * ((M11 * M22) - (M12 * M21)),
			0.0f,
			s * (M21*(M33*M42 - M32*M43) + M22*(M31*M43 - M33*M41) + M23*(M32*M41 - M31*M42)),
			s * (M31*(M13*M42 - M12*M43) + M32*(M11*M43 - M13*M41) + M33*(M12*M41 - M11*M42)),
			s * (M41*(M13*M22 - M12*M23) + M42*(M11*M23 - M13*M21) + M43*(M12*M21 - M11*M22)),
			1.0f);
	}

    vector2d transform(const vector2d& _v) const
	{
		float d = (M14 * _v.x + M24 * _v.y + M44);
		if (fabs(d) < EPS) return vector2d();

		d = 1.0f / d;
		return vector2d((M11 * _v.x + M21 * _v.y + M41) * d,
						(M12 * _v.x + M22 * _v.y + M42) * d);
	}

    vector2d& position() const
	{
		return *(vector2d*)&M41;
	}

    void rotateZ(const float _a)
	{
		float c = cos(_a);
		float s = sin(_a);
		for (int i = 0; i < 4; i++) 
		{
			float mi0 = m[i][0];
			float mi1 = m[i][1];
			m[i][0] = mi0 * c + mi1 * -s;
			m[i][1] = mi0 * s + mi1 * c;
		}
	}

    void translate(const vector2d& _t)
	{
		M41 += _t.x;
		M42 += _t.y;
	}

    void setTranslation(const vector2d& _t)
	{
		M41 = _t.x;
		M42 = _t.y;
	}

	void makeOrtho(float w, float h, float zn, float zf)
	{
		M11 = 2.0f / w; M12 = 0.0f;     M13 = 0.0f;             M14 = 0.0f;
		M21 = 0.0f;     M22 = 2.0f / h; M23 = 0.0f;             M24 = 0.0f;
		M31 = 0.0f;     M32 = 0.0f;     M33 = 1.0f / (zn - zf); M34 = 0.0f;
		M41 = 0.0f;     M42 = 0.0f;     M43 = zn / (zn - zf);   M44 = 1.0f;
	}

	void operator*=(const matrix& m1)
	{
		for (int i = 0; i < 4; i++)
		{
			float mi0 = m[i][0];
			float mi1 = m[i][1];
			float mi2 = m[i][2];
			float mi3 = m[i][3];
			m[i][0] = mi0*m1.m[0][0] + mi1*m1.m[1][0] + mi2*m1.m[2][0] + mi3*m1.m[3][0];
			m[i][1] = mi0*m1.m[0][1] + mi1*m1.m[1][1] + mi2*m1.m[2][1] + mi3*m1.m[3][1];
			m[i][2] = mi0*m1.m[0][2] + mi1*m1.m[1][2] + mi2*m1.m[2][2] + mi3*m1.m[3][2];
			m[i][3] = mi0*m1.m[0][3] + mi1*m1.m[1][3] + mi2*m1.m[2][3] + mi3*m1.m[3][3];
		}
	}

    float m[4][4];
};

}
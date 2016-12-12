#pragma once
#include <math.h>
#include "Vector3D.h"

inline Vec3f CalcCadinal(float u, float tension
	, Vec3f P0, Vec3f P1, Vec3f P2, Vec3f P3)
{
	float s = (1.0f - tension) * 0.5f;

	Vec3f a = -s * P0 + (2.0f - s)*P1 + (s - 2.0f)*P2 + s * P3;
	Vec3f b = 2.0f * s * P0 + (s - 3.0f)* P1 + (3.0f - 2.0f * s)*P2 - s*P3;
	Vec3f c = -s*P0 + s*P2;
	Vec3f d = P1;

	return (a*pow(u, 3.0f) + b*pow(u, 2.0f) + c*u + d);
}
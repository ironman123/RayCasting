#pragma once
#include <cmath>
#include "Vec2.h"

template <typename T>
auto sq(T x)
{
	return x * x;
}

inline auto GetS(float a, float b, float c)
{
	return sq(b) - (4.0f * a * c);
}

inline auto GetQuadraticRoots(float a, float b, float c)
{
	const float B = std::sqrt(GetS(a,b,c)) / (2.0f * a);
	if (B < 0.0f)
	{
		return std::make_pair(0.0f, 0.0f);
	}
	else
	{
		const float A = -b / (2.0f * a);
		const float x1 = A + B;
		const float x2 = A - B;

		return std::make_pair(x1, x2);
	}
}

template <typename T>
T DistancePointToLine(const Vec2<T>& l0, const Vec2<T>& l1, const Vec2<T>& p)
{
	const T A = l0.y - l1.y;
	const T B = l1.x - l0.x;
	const T C = (l0.x * l1.y) - (l1.x * l0.y);

	return std::abs((A * p.x + B * p.y + C) / std::sqrt(sq(A) + sq(B)));
}

template <typename T>
T DistanceSqBetween2Points(const Vec2<T>& p0, const Vec2<T>& p1)
{
	const float dy = p1.y - p0.y;
	const float dx = p1.x - p0.x;

	return sq(dy) + sq(dx);
}

template <typename T>
T DistanceBetween2Points(const Vec2<T>& p0, const Vec2<T>& p1)
{
	const float dy = p1.y - p0.y;
	const float dx = p1.x - p0.x;

	return  std::sqrt::(sq(dy) + sq(dx));
}

template <typename T>
Vec2<T> NormalToLine(const Vec2<T>& l0, const Vec2<T>& l1)
{
	const float dy = l1.y - l0.y;
	const float dx = l1.x - l0.x;
	if (dy == (T)0)
	{
		return Vec2<T>{(T)0, (T)1};
	}
	else if (dx == (T)0)
	{
		return Vec2<T>{(T)1, (T)0};
	}
	else
	{
		//returns upward normal.
		//for downward normal multiply the returned vector by -1.
		return Vec2<T>{dy, -dx}.Normalize();
	}
}
#pragma once
#include <cmath>
#include "Vec2.h"

template <typename T>
auto sq(T x)
{
	return x * x;
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
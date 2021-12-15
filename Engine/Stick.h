#pragma once
#include "Point.h"
#include <vector>

class Stick
{
public:
	Stick() = default;
	Stick(const Point& p0, const Point& p1)
	{
		points.emplace_back(p0);
		points.emplace_back(p1);

		length = ((Vef2)points[1] - (Vef2)points[0]).Length();
		lengthSq = (length * length);
	}
	float GetDistance()const
	{
		return ((Vef2)points[1] - (Vef2)points[0]).Length();
	}
	float GetDistanceSq()const
	{
		return ((Vef2)points[1] - (Vef2)points[0]).LengthSq();
	}
	Vef2 GetStickVec()const
	{
		return (Vef2)points[1] - (Vef2)points[0];
	}
public:
	std::vector<Point> points;
	float length = 0.0f;
	float lengthSq = 0.0f;
};
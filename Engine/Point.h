#pragma once
#include "Vec2.h"

class Point
{
public:
	Point() = default;
	Point(const Vef2& pos, const Vef2& oldPos)
		:
		pos(pos),
		oldPos(oldPos)
	{}
	explicit operator Vef2()const
	{
		return pos;
	}
public:
	Vef2 pos = {0.0f, 0.0f};
	Vef2 oldPos = pos;
};
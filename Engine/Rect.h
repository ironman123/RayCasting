#pragma once
#include "Vec2.h"

class Rect
{
public:
	Rect() = default;
	Rect(int left_in, int right_in, int top_in, int bottom_in);
	Rect(const Vec2& topLeft, const Vec2& bottomRight);
	Rect(const Vec2& topLeft, int widht, int height);
	bool IsOverLappingWith(const Rect& other)const;
	bool IsPointInside(const Vec2& point)const;
	static Rect FromCenter(const Vec2& center, int halfWidht, int halfHeight);
	Vec2 GetCenter()const;
public:
	int left;
	int right;
	int top;
	int bottom;
};
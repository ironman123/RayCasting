#include "Rect.h"

Rect::Rect(int left_in, int right_in, int top_in, int bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

Rect::Rect(const Vec2& topLeft, const Vec2& bottomRight)
	:
	Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Rect::Rect(const Vec2& topLeft, int widht, int height)
	:
	Rect(topLeft, topLeft + Vec2(widht, height))
{
}

bool Rect::IsOverLappingWith(const Rect& other) const
{
	return(other.right >= left && other.left <= right && other.bottom >= top && other.top <= bottom);
}

bool Rect::IsPointInside(const Vec2& point) const
{
	return(point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
}

Rect Rect::FromCenter(const Vec2& center, int halfWidht, int halfHeight)
{
	const Vec2 half = { halfWidht, halfHeight };
	return Rect(center - half, center + half);
}

Vec2 Rect::GetCenter() const
{
	return Vec2((left + right) / 2, (top + bottom) / 2);
}



#pragma once
#include "Vec2.h"

template <typename T>
class Rect
{
public:
	Rect() = default;
	Rect(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{
	}
	Rect(const Vec2<T>& topLeft, const Vec2<T>& bottomRight)
		:
		Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{
	}
	Rect(const Vec2<T>& topLeft, T widht, T height)
		:
		Rect(topLeft, topLeft + Vec2<T>(widht, height))
	{
	}
	Rect operator*(T scale)const
	{
		return RectF(left * scale, right * scale, top * scale, bottom * scale);
	}
	Rect& operator*=(T scale)
	{
		return *this = *this * scale;
	}
	T GetWidth()const
	{
		return right - left;
	}
	T GetHeight()const
	{
		return bottom - top;
	}
	bool IsContainedBy(const Rect& other)const
	{
		return left >= other.left && right <= other.right 
			&& bottom >= other.bottom && top <= other.top;
	}
	bool ContainsPoint(const Vec2<T>& point)const
	{
		return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
	}
	bool IsOverLappingWith(const Rect& other)const
	{
		return(other.right >= left && other.left <= right && other.bottom >= top && other.top <= bottom);
	}
	static Rect FromCenter(const Vec2<T>& center, T halfWidht, T halfHeight)
	{
		const Vec2<T> half = { halfWidht, halfHeight };
		return Rect(center - half, center + half);
	}
	Rect GetExpanded(T offset)const
	{
		return Rect(left - offset, right + offset, top - offset, bottom + offset);
	}
	Vec2<T> GetCenter()const
	{
		return Vec2<T>((left + right) / 2, (top + bottom) / 2);
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect<float> RectF;
typedef Rect<int> RectI;
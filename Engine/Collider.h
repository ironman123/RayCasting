#pragma once
#include "Rect.h"

template <typename T>
class Collider
{
public:
	static bool IsColliding(const Rect<T>& obj0, const Rect<T>& obj1)
	{
		return obj0.IsOverLappingWith(obj1);
	}
};
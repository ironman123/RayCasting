#pragma once
#include "Entity.h"
#include "Rect.h"

class Boundary : public Entity
{
public:
	Boundary(const Vef2& pos, float halfWidth, float halfHeight, Color c = Colors::Cyan)
		:
		rect(-halfWidth,halfWidth,halfHeight,-halfHeight),
		Entity({ {pos.x - halfWidth,pos.y - halfHeight},{pos.x - halfWidth, pos.y + halfHeight},{pos.x + halfWidth, pos.y + halfHeight},{pos.x + halfWidth, pos.y - halfHeight} }, pos, c),
		width(halfWidth * 2.0f),
		height(halfHeight *2.0f)
	{}
	float GetWidth()const
	{
		return width * GetScale();
	}
	float GetHeight()const
	{
		return height * GetScale();
	}
	RectF GetRect()const override
	{
		return rect * GetScale();
	}
public:
	float GetRadius()const
	{
		return 0.0f;
	}
	Vef2 GetVel()const
	{
		return Vef2{ 0.0f,0.0f };
	}
	void SetVel(const Vef2& vel)
	{

	}
private:
	Vef2 vel = { 0.0f,0.0f };
	RectF rect;
	float width;
	float height;
};
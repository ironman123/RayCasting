#pragma once
#include "Entity.h"
#include "Star.h"
#include "ChiliMath.h"

class Ball : public Entity
{
public:
	Ball(Vef2 pos, float radius, Vef2 vel, Color c = Colors::Red)
		:
		spwanPos(pos),
		Entity(Star::Make(radius, radius, 8), pos, c),
		radius(radius),
		vel(vel)
	{
	}
	float GetRadius()const
	{
		return radius;
	}
	Vef2 GetVel()const
	{
		return vel;
	}
	void SetVel(const Vef2& vel_in)
	{
		vel = vel_in;
	}
	bool IsSpwaned()const
	{
		return isSpwaned;
	}
	void Update(float dt)
	{
		TranslateBy(vel * dt);
		if (!isSpwaned && DistanceSqBetween2Points(GetPos(),spwanPos) > sq(GetRadius() * 2.0f))
		{
			isSpwaned = true;
		}
	}
private:
	Vef2 spwanPos;
	bool isSpwaned = false;
	float radius;
	Vef2 vel;
};
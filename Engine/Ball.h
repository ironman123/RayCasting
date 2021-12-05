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
		Entity(Star::Make(radius, radius - 5.0f, 8), pos, c),
		radius(radius),
		vel(vel)
	{
	}
	float GetRadius() const override
	{
		return radius;
	}
	Vef2 GetVel() const override
	{
		return vel;
	}
	void SetVel(const Vef2& vel_in) override
	{
		vel = vel_in;
	}
	void Update(float dt)
	{
		//temp angle update for testing
		SetAngle(angle += dt);
		TranslateBy(vel * dt);
	}
private:
	float angle = 0.0f;
	Vef2 spwanPos;
	bool isSpwaned = false;
	float radius;
	Vef2 vel;
};
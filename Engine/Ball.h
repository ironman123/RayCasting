#pragma once
#include "Entity.h"
#include "Star.h"
#include "ChiliMath.h"

class Ball : public Entity
{
public:
	Ball(Vef2 pos, float radius, Vef2 vel, Color c = Colors::Red)
		:
		Entity(Star::Make(radius, radius, 8), pos, c),
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
	RectF GetRect()const
	{
		return RectF(-radius, radius, radius, -radius);
	}
private:
	float angle = 0.0f;
	bool isSpwaned = false;
	float radius;
	Vef2 vel;
};
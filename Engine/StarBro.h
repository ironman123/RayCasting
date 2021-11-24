#pragma once
#include "Star.h"
#include "Entity.h"

class StarBro : public Entity
{
public:
	StarBro(float radius, float innerRatio, std::mt19937& rng, Vef2 pos, int nFlares, Color c)
		:
		speedRange(0.9f,1.0f),
		Entity(Star::Make(radius, innerRatio * radius, nFlares),pos, c),
		radius(radius),
		speed(speedRange(rng))
	{}
	float GetRadius() const
	{
		return radius;
	}
	void Update(float dt, std::mt19937& rng ,Drawable& d)
	{
		rad += dt;
		float ratio = std::abs(sin( speed * 3.14159 * rad));
		SetScale( 1.0f * ratio);
	}
private:
	std::normal_distribution<float> speedRange;
	float speed;
	float rad = 0.0f;
	float radius;
};
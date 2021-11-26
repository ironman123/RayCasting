#pragma once
#include "Star.h"
#include "Entity.h"
#include "Rect.h"

class StarBro : public Entity
{
public:
	StarBro(float radius, float innerRatio, float colorFrequency, float colorPhase, float scaleAmplitude, float scaleFrequency, float scalePhase, Vef2 pos, int nFlares, Color c)
		:
		baseColor(c),
		colorFreqFactor(colorFrequency * 2.0f * 3.14159f),
		colorPhase(colorPhase),
		scaleAmplitude(scaleAmplitude),
		scaleFreqFactor(scaleFrequency * 2.0f * 3.14159f),
		scalePhase(scalePhase),
		Entity(Star::Make(radius, innerRatio* radius, nFlares), pos, baseColor),
		radius(radius)
	{}
	float GetRadius() const
	{
		return radius * GetScale();
	}
	float GetMaxRadius() const
	{
		return radius * (1.0f + scaleAmplitude);
	}
	void Update(float dt)
	{
		time += dt;
		UpdateColor();
		UpdateScale();
	}
	void UpdateColor()
	{
		Color c;
		const int offset = int(127.0f * sin(colorFreqFactor * time + colorPhase)) + 128;
		c.SetR(std::min(baseColor.GetR() + offset, 255));
		c.SetG(std::min(baseColor.GetG() + offset, 255));
		c.SetB(std::min(baseColor.GetB() + offset, 255));
		SetColor(c);
	}
	void UpdateScale()
	{
		const float newScale = (scaleAmplitude * sin(scaleFreqFactor * time + scalePhase)) + 1.0f;
		SetScale(newScale);
	}
	RectF GetRect()const
	{
		return RectF::FromCenter(GetPos(), GetRadius(), GetRadius());
	}
private:
	Color baseColor;
	float radius;
	float colorFreqFactor;
	float colorPhase;
	float scaleAmplitude;
	float scaleFreqFactor;
	float scalePhase;
	float time = 0.0f;
};
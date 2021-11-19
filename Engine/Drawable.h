#pragma once
#include "Vec2.h"
#include <vector>
#include "Graphics.h"

class Drawable
{
public:
	Drawable(std::vector<Vef2> model, Color c)
		:
		c(c),
		model(model)
	{}
	void Translate(const Vef2& translation_in)
	{
		translation += translation_in;
	}
	void Scale(float scale_in)
	{
		translation *= scale_in;
		scaleX *= scale_in;
		scaleY *= scale_in;
	}
	void ScaleIndependent(float scaleX_in, float scaleY_in)
	{
		translation.x *= scaleX_in;
		translation.y *= scaleY_in;
		scaleX *= scaleX_in;
		scaleY *= scaleY_in;
	}
	void Render(Graphics& gfx)
	{
		for (auto& v : model)
		{
			v.x *= scaleX;
			v.y *= scaleY;
			v += translation;
		}
		gfx.DrawClosedPolyline(model, c);
	}
private:
	Color c;
	std::vector<Vef2> model;
	Vef2 translation = { 0.0f,0.0f };
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	
};
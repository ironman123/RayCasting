#pragma once
#include "Vec2.h"
#include <vector>
#include "Graphics.h"
#include <memory>
#include "Mat3.h"
#include "Point.h"

class Drawable
{
public:
	Drawable(const std::vector<Vef2>& model, Color c)
		:
		c(c),
		model(&model)
	{}
	void ApplyTransformation(const Maf3& transformatin_in)
	{
		transformation = transformatin_in * transformation;
	}
	void Render(Graphics& gfx)
	{
		gfx.DrawClosedPolyline(*model, transformation, c);
	}
private:
	Color c;
	const std::vector<Vef2>* model;
	Maf3 transformation = Maf3::Identity();
};
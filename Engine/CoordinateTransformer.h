#pragma once
#include <vector>
#include "Vec2.h"
#include "Drawable.h"
#include "Graphics.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer(Graphics& gfx)
		:
		gfx(gfx)
	{}
	void Draw(Drawable& drawable)const
	{
		const Vef2 offset = { Graphics::ScreenWidth / 2,Graphics::ScreenHeight / 2 };

		drawable.ApplyTransformation(Maf3::Translation(offset) * Maf3::ScaleIndependent(1.0f, -1.0f));
		drawable.Render(gfx);
	}
private:
	Graphics& gfx;
};
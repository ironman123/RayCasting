#pragma once
#include "CoordinateTransformer.h"
#include "Rect.h"

class Camera
{
public:
	Camera(CoordinateTransformer& ct)
		:
		ct(ct)
	{}
	const Vef2& GetPos()const
	{
		return pos;
	}
	void MoveTo(const Vef2& pos_in)
	{
		pos = pos_in;
	}
	void MoveBy(const Vef2& offset)
	{
		pos += offset;
	}
	float GetScale()const
	{
		return scale;
	}
	void SetScale(float val)
	{
		scale = val;
	}
	void Draw(Drawable& drawable)const
	{
		drawable.Translate(-pos);
		drawable.Scale(scale);
		ct.Draw(drawable);
	}
	RectF GetViewPort()const
	{
		const float zoom = 1.0f / scale;
		return RectF::FromCenter(pos, float(Graphics::ScreenWidth / 2) * zoom, float(Graphics::ScreenHeight / 2) * zoom);
	}
private:
	CoordinateTransformer& ct;
	Vef2 pos = { 0.0f,0.0f };
	float scale = 1.0f;
};

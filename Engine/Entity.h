#pragma once
#include "Vec2.h"
#include <vector>
#include "Drawable.h"

class Entity
{
public:
	Entity(std::vector<Vef2> model, const Vef2& pos_in = { 0.0f,0.0f }, Color c = Colors::Yellow)
		:
		c(c),
		pos(pos_in),
		model(std::move(model))
	{
	}
	void SetPos(const Vef2& newPos)
	{
		pos = newPos;
	}
	const Vef2& GetPos()const
	{
		return pos;
	}
	void TranslateBy(const Vef2& offset)
	{
		pos += offset;
	}
	void SetScale(float val)
	{
		scale = val;
	}
	void SetColor(Color c_in)
	{
		c = c_in;
	}
	float GetScale()const
	{
		return scale;
	}
	Drawable GetDrawable()const
	{
		Drawable d(model, c);
		d.Scale(scale);
		d.Translate(pos);
		
		return d;
	}
protected:
	void SetModel(std::vector<Vef2> model_in)
	{
		model = std::move(model_in);
	}
private:
	Color c;
	float scale = 1.0f;
	Vef2 pos;
	std::vector<Vef2> model;
};
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
	float GetAngle()const
	{
		return angle;
	}
	void SetAngle(float a)
	{
		angle = a;
	}
	Drawable GetDrawable()const
	{
		Drawable d(model, c);

		d.ApplyTransformation(Maf3::Translation(pos) * Maf3::Scale(scale) * Maf3::Rotate(angle));
		
		return d;
	}
/********************************/
//virtual Functions Start
	virtual float GetRadius()const = 0;
	virtual Vef2 GetVel()const =  0;
	virtual void SetVel(const Vef2& vel_in) = 0;
//virtual Functions End
/********************************/
protected:
	void SetModel(std::vector<Vef2> model_in)
	{
		model = std::move(model_in);
	}
private:
	Color c;
	float angle = 0.0f;
	float scale = 1.0f;
	Vef2 pos;
	std::vector<Vef2> model;
};
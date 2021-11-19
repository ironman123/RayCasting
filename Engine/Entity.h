#pragma once
#include "Vec2.h"
#include <vector>

class Entity
{
public:
	Entity(std::vector<Vef2> model, const Vef2& pos_in = { 0.0f,0.0f })
		:
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
	float GetScale()const
	{
		return scale;
	}
	std::vector<Vef2> GetPolyline()const
	{
		auto poly = model;
		for (auto& v : poly)
		{
			v *= scale;
			v += pos;
		}
		return poly;
	}
private:
	float scale = 1.0f;
	Vef2 pos;
	std::vector<Vef2> model;
};
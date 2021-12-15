#pragma once
#include "Point.h"
#include <vector>
#include "Drawable.h"

class PointEntity
{
public:
	PointEntity(std::vector<Point> model, const Vef2& pos = { 0.0f,0.0f }, Color c = Colors::Red)
		:
		c(c),
		pos(pos),
		model(std::move(model))
	{
		for (const auto& p : model)
		{
			vModel.emplace_back(p.pos);
		}
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
	std::vector<Vef2>* GetModel()
	{
		for (int i = 0; i < model.size(); i++)
		{
			vModel[i] = model[i].pos;
		}
		return &vModel;
	}
	std::vector<Point>* GetPtrModel()
	{
		return std::addressof(model);
	}
	Drawable GetDrawable()
	{
		Drawable d(*GetModel(), c); 
		d.ApplyTransformation(Maf3::Translation(pos));
		return d;
	}
	void SetModel(std::vector<Point> model_in)
	{
		model = std::move(model_in);
		for (const auto& p : model)
		{
			vModel.emplace_back(p.pos);
		}
	}
private:
	std::vector<Point> model;
	std::vector<Vef2> vModel;
	Color c;
	Vef2 pos;
};
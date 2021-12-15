#pragma once
#include "Stick.h"
#include <vector>
#include "Drawable.h"

class StickEntity
{
public:
	StickEntity(std::vector<Stick> model, const Vef2& pos = { 0.0f,0.0f }, Color c = Colors::Green)
		:
		c(c),
		pos(pos),
		model(std::move(model))
	{
	}
	void SetPos(const Vef2& newPos)
	{
		pos = newPos;
		for (const auto& p : model)
		{
			vModel.emplace_back(p.points[0].pos);
			pModel.emplace_back(p.points[0]);
		}
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
			vModel[i] = model[i].points[0].pos;
		}
		return std::addressof(vModel);
	}
	std::vector<Point>* GetPtModel()
	{
		for (int i = 0; i < model.size(); i++)
		{
			pModel[i] = model[i].points[0];
		}
		return std::addressof(pModel);
	}
	std::vector<Stick>* GetStModel()
	{
		return std::addressof(model);
	}
	Drawable GetDrawable()
	{
		Drawable d(*GetModel(), c);
		d.ApplyTransformation(Maf3::Translation(pos));
		return d;
	}
	void Update()
	{
		for (int i = 0; i < model.size(); i++)
		{
			vModel[i] = model[i].points[0].pos;
			pModel[i] = model[i].points[0];
		}
	}
	void SetModel(std::vector<Stick> model_in)
	{
		model = std::move(model_in);
		for (const auto& s : model)
		{
			vModel.emplace_back(s.points[0].pos);
			pModel.emplace_back(s.points[0]);
		}
	}
private:
	std::vector<Stick> model;
	std::vector<Point> pModel;
	std::vector<Vef2> vModel;
	Vef2 pos;
	Color c;
};
#pragma once
#include "Entity.h"
#include "Graphics.h"
#include "Vec2.h"
#include <algorithm>

class Plank : public Entity
{
public:
	Plank(Vef2 anchor, float freeX, float minFreeY, float maxFreeY, float fatness = 8.0f, Color c = Colors::Yellow)
		:
		Entity({}, anchor, c),
		minFreeYModel(minFreeY - anchor.y),
		maxFreeYModel(maxFreeY - anchor.y),
		freePtModel(freeX - anchor.x, minFreeYModel),
		fatness(fatness)
	{

	}
	Drawable GetDrawable()
	{
		std::vector<Vef2> model;
		model.reserve(4);
		model.emplace_back(0.0f, 0.0f);
		model.emplace_back(freePtModel);
		model.emplace_back(freePtModel + Vef2{ 0.0f,fatness });
		model.emplace_back(0.0f, fatness);
		SetModel(std::move(model));
		return Entity::GetDrawable();
	}
	Vef2 GetFreePt()const
	{
		return freePtModel + GetPos();
	}
	void SetFreeY(float freeY_in)
	{
		freePtModel.y = std::clamp(freeY_in - GetPos().y, minFreeYModel, maxFreeYModel);
	}
	void MoveFreeY(float delta)
	{
		SetFreeY(GetFreePt().y + delta);
	}
	Vef2 GetPlankSurfaceVector()const
	{
		return -freePtModel;
	}
	float GetPlankThiccness()const
	{
		return fatness;
	}
	auto GetPoints()const
	{
		return std::make_pair(GetPos(), GetFreePt());
	}

	float GetRadius() const override
	{
		return 0.0f;
	}
	Vef2 GetVel() const override
	{
		return Vef2{ 0.0f,0.0f };
	}
	void SetVel(const Vef2& val) override
	{

	}

private:
	float fatness;
	float minFreeYModel;
	float maxFreeYModel;
	Vef2 freePtModel;
};
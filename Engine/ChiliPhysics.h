#pragma once
#include "Entity.h"
#include "Ball.h"
#include "ChiliMath.h"

inline void DoBallCollision(Entity* e0, Entity* e1)
{
	const float b1_rad = e0->GetRadius();
	const float b2_rad = e1->GetRadius();
	const float b1_dia = b1_rad * 2.0f;
	const float b2_dia = b2_rad * 2.0f;

	const Vef2 bP1 = e0->GetPos();
	const Vef2 bP2 = e1->GetPos();
	const Vef2 ballVec = bP2 - bP1;

	const float distance = ballVec.LengthSq();
	if (distance <= sq(e0->GetRadius() + e1->GetRadius()))
	{
		const Vef2 normalBallVec = ballVec.GetNormalized();

		//Collision Color Set
		e0->SetColor(Colors::Cyan);
		e1->SetColor(Colors::Cyan);

		//const Vef2 n = -NormalToLine(bP2, bP1);
		const Vef2 vB1 = e0->GetVel();
		const Vef2 vB2 = e1->GetVel();

		const Vef2 relVel = (vB2 - vB1);
		const Vef2 relNormalVel = relVel.GetNormalized();

		const auto roots = GetQuadraticRoots(1.0f, 2.0f * (ballVec * relNormalVel), (ballVec * ballVec) - (b1_dia * b2_dia));

		//const float dBV = (roots.first < roots.second ? roots.first : roots.second);
		//relative distance traveled by each ball
		const float dBV = std::abs(roots.first < roots.second ? roots.first : roots.second) / relVel.Length();

		const float dB1 = dBV * (vB1.Length());
		const float dB2 = dBV * (vB2.Length());

		const Vef2 dAdjustB1 = vB1.GetNormalized() * dB1;
		const Vef2 dAdjustB2 = vB2.GetNormalized() * dB2;

		//distance b/w balls before adjustment test
		//const auto a = (e1.GetPos() - e0.GetPos()).Length();

		e0->TranslateBy(-dAdjustB1);
		e1->TranslateBy(-dAdjustB2);

		//distance b/w balls after adjustment test
		//const auto b = (e1.GetPos() - e0.GetPos()).Length();

		//const Vef2 n2 = NormalToLine(e0.GetPos(), e1.GetPos());

		const Vef2 changedRelativeVel = normalBallVec * (relVel * normalBallVec);

		const Vef2 newVB1 = vB1 + changedRelativeVel;
		const Vef2 newVB2 = vB2 - changedRelativeVel;

		const Vef2 newDAdjustB1 = newVB1.GetNormalized() * dB1;
		const Vef2 newDAdjustB2 = newVB2.GetNormalized() * dB2;

		e0->TranslateBy(newDAdjustB1);
		e1->TranslateBy(newDAdjustB2);

		//distance b/w balls after second adjustment test
		//const auto c = (e1.GetPos() - e0.GetPos()).Length();

		e0->SetVel(newVB1);
		e1->SetVel(newVB2);
	}
}
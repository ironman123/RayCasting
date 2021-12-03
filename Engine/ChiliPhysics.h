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

		const Vef2 vB1 = e0->GetVel();
		const Vef2 vB2 = e1->GetVel();

		const Vef2 relVel = (vB2 - vB1);
		const Vef2 relNormalVel = relVel.GetNormalized();

		const auto roots = GetQuadraticRoots(1.0f, 2.0f * (ballVec * relNormalVel), (ballVec * ballVec) - (b1_dia * b2_dia));

		//relative distance traveled by each ball
		const float dBV = std::abs(roots.first < roots.second ? roots.first : roots.second) / relVel.Length();

		//actual distance traveled by each ball
		const float dB1 = dBV * (vB1.Length());
		const float dB2 = dBV * (vB2.Length());

		const Vef2 dAdjustB1 = vB1.GetNormalized() * dB1;
		const Vef2 dAdjustB2 = vB2.GetNormalized() * dB2;

		e0->TranslateBy(-dAdjustB1);
		e1->TranslateBy(-dAdjustB2);

		//relVel * normalBallVec will always give -ve valuse try and calculate
		const Vef2 changedRelativeVel = normalBallVec * (relVel * normalBallVec);

		const Vef2 newVB1 = vB1 + changedRelativeVel;
		const Vef2 newVB2 = vB2 - changedRelativeVel;

		const Vef2 newDAdjustB1 = newVB1.GetNormalized() * dB1;
		const Vef2 newDAdjustB2 = newVB2.GetNormalized() * dB2;

		e0->TranslateBy(newDAdjustB1);
		e1->TranslateBy(newDAdjustB2);

		e0->SetVel(newVB1);
		e1->SetVel(newVB2);
	}
}

template <typename T>
inline void DoBoundaryCollision(const std::pair<Vec2<T>, Vec2<T>> points, Entity* e)
{
	const Vef2 w = NormalToPointFromLine(points.first, points.second, e->GetPos());

	e->SetColor(Colors::Green);
	const Vef2 v = e->GetVel();
	//const Vef2 distAdjust = (-e->GetVel().GetNormalized()) * 2.0f * (e.GetRadius() - std::min(bottomDist, topDist));

	e->SetVel(v - w * (2.0f * (w * v)));
}
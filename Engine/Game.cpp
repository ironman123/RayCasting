/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <random>
#include "Star.h"
#include <algorithm>
#include "ChiliMath.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	ct(gfx),
	cam(ct),
	camCtrl(cam,wnd.mouse),
	plank({ 180.0f,150.0f }, -240.0f, -270.0f, 300.0f),
	spwaner(balls, radius, Vef2{ 0.0f,-180.0f }, 75.0f, -12.0f, 12.0f, 1.9f)
{
	
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	camCtrl.Update();

	float dt = ft.Mark();
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		plank.MoveFreeY(-2.0f);
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		plank.MoveFreeY(2.0f);
	}

	if (wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		balls.erase(balls.begin(), balls.end());
	}

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		spwaner.BallPairSpwaner(dt);
	}

	for (size_t i = 0; i < balls.size(); ++i)
	{
		balls[i].Update(dt);

		const auto plankPts = plank.GetPoints();

		for (size_t j = 0; j < balls.size(); ++j)
		{
			if (i == j)
			{
				continue;
			}
			const Vef2 bP1 = balls[i].GetPos();
			const Vef2 bP2 = balls[j].GetPos();
			const Vef2 ballVec = bP2 - bP1;

			const float distance = ballVec.LengthSq();
			if (distance <= sq(minBallColDist))
			{
				balls[i].SetColor(Colors::Cyan);
				balls[j].SetColor(Colors::Cyan);

				const Vef2 n = -NormalToLine(bP2, bP1);
				const Vef2 vB1 = balls[i].GetVel();
				const Vef2 vB2 = balls[j].GetVel();

				const Vef2 relVel = (vB2 - vB1);
				const Vef2 relNormalVel = relVel.GetNormalized();

				const auto roots = GetQuadraticRoots(1.0f, 2.0f * (ballVec * relNormalVel), (ballVec * ballVec) - deltaRadSq);

				//const float dBV = (roots.first < roots.second ? roots.first : roots.second);
				const float dBV = std::abs(std::min(roots.first, roots.second));
				
				const float dB1 = (dBV * (vB1.Length())) / relVel.Length();
				const float dB2 = (dBV * (vB2.Length())) / relVel.Length();

				const Vef2 dAdjustB1 = vB1.GetNormalized() * dB1;
				const Vef2 dAdjustB2 = vB2.GetNormalized() * dB2;

				//distance b/w balls before adjustment test
				const auto a = (balls[j].GetPos() - balls[i].GetPos()).Length();

				balls[i].TranslateBy(-dAdjustB1);
				balls[j].TranslateBy(-dAdjustB2);

				//distance b/w balls after adjustment test
				const auto b = (balls[j].GetPos() - balls[i].GetPos()).Length();

				const Vef2 n2 = NormalToLine(balls[i].GetPos(), balls[j].GetPos());

				const Vef2 newVB1 = (n2 * (vB1 * n2)) * 2.0f - vB1;
				const Vef2 newVB2 = (n2 * (vB2 * n2)) * 2.0f - vB2;

				const Vef2 newDAdjustB1 = newVB1.GetNormalized() * dB1;
				const Vef2 newDAdjustB2 = newVB2.GetNormalized() * dB2;

				balls[i].TranslateBy(newDAdjustB1);
				balls[j].TranslateBy(newDAdjustB2);

				//distance b/w balls after second adjustment test
				const auto c = (balls[j].GetPos() - balls[i].GetPos()).Length();

				balls[i].SetVel(newVB1);
				balls[j].SetVel(newVB2);
				
			}
		}

		if (DistancePointToLine(plankPts.first, plankPts.second, balls[i].GetPos()) < balls[i].GetRadius() && NormalToLine(plankPts.first, plankPts.second) * balls[i].GetVel() > 0.0f)
		{
			balls[i].SetColor(Colors::Green);
			const Vef2 w = plank.GetPlankSurfaceVector().GetNormalized();
			const Vef2 v = balls[i].GetVel();
			//balls[i].SetVel((w * (v * w)) * 2.0f - v);
		}

	}
	spwaner.BallPairSpwaner(dt);
	//spwaner.Update(dt);

	const auto newEnd = std::remove_if(balls.begin(), balls.end(), [this](const Ball& ball) {return ball.GetPos().LengthSq() > maxBallDist * maxBallDist; });
	balls.erase(newEnd, balls.end());
}

void Game::ComposeFrame()
{
	cam.Draw(plank.GetDrawable());
	
	for (auto& ball : balls)
	{
		cam.Draw(ball.GetDrawable());
	}
}

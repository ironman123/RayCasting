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
#include "ChiliPhysics.h"
#include "Mat3.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	ct(gfx),
	cam(ct),
	camCtrl(cam, wnd.mouse, wnd.kbd),
	plank({ 180.0f,150.0f }, -240.0f, -270.0f, 300.0f),
	spwaner(balls, radius, Vef2{ 0.0f,180.0f }, -50.0f, -12.0f, 12.0f, 1.8f)
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
	float dt = ft.Mark();

	camCtrl.Update(dt);
	
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
			DoBallCollision(&balls[i], &balls[j]);
		}

		const Vef2 plankThickenss = Vef2{ 0.0f,plank.GetPlankThiccness() };
		const float bottomDist = DistancePointToLine(plankPts.first, plankPts.second, balls[i].GetPos());
		const float topDist = DistancePointToLine(plankPts.first + plankThickenss, plankPts.second + plankThickenss, balls[i].GetPos());

		if (bottomDist < balls[i].GetRadius() || topDist < balls[i].GetRadius())
		{
			//DoBoundaryCollision(std::make_pair(plankPts.first, plankPts.second), &balls[i]);
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

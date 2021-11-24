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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	ct(gfx),
	cam(ct)
{
	std::uniform_real_distribution<float> xDist(-fieldWidth / 2.0f, fieldWidth / 2.0f);
	std::uniform_real_distribution<float> yDist(-fieldHeight / 2.0f, fieldHeight / 2.0f);
	std::normal_distribution<float> radDist(meanRadius, devRadius);
	std::normal_distribution<float> ratDist(meanRatio, devRatio);
	std::normal_distribution<float> flareDist(meanFlares, devFlares);

	const Color colors[] = { Colors::Red, Colors::Green, Colors::Yellow, Colors::Blue, Colors::Cyan, Colors::White, Colors::Magenta };
	std::uniform_int_distribution<size_t> cDist(0, std::end(colors) - std::begin(colors));

	while (stars.size() < nStars)
	{
		const auto rad = std::clamp(radDist(rng), minRadius, maxRadius);
		const Vef2 pos = { xDist(rng), yDist(rng) };

		if (std::any_of(stars.begin(), stars.end(), [&](const StarBro& sb) { return (sb.GetPos() - pos).Length() < sb.GetRadius() + rad; }))
		{
			continue;
		}

		const auto ratio = std::clamp(ratDist(rng), minRatio, maxRatio);
		const auto flares = std::clamp((int)flareDist(rng), minnFlares, maxnFlares);
		const Color c = colors[cDist(rng)];

		stars.emplace_back(rad, ratio, rng, pos, flares, c);
	}
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
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::WheelUp)
		{
			cam.SetScale(cam.GetScale() * 1.05f);
		}
		if (e.GetType() == Mouse::Event::Type::WheelDown)
		{
			cam.SetScale(cam.GetScale() * 0.95f);
		}
	}

	float speed = 3.0f;
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		cam.MoveBy({ 0.0f, speed });
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		cam.MoveBy({ 0.0f, -speed });
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		cam.MoveBy({ -speed, 0.0f });
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		cam.MoveBy({ speed, 0.0f });
	}

	float dt = ft.Mark();

	for (auto& e : stars)
	{
		e.Update(dt, rng, e.GetDrawable());
	}
}

void Game::ComposeFrame()
{
	for (auto& e : stars)
	{
		cam.Draw(e.GetDrawable());
	}
}

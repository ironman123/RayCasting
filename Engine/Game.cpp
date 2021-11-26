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
	cam(ct),
	camCtrl(cam,wnd.mouse)
{
	std::uniform_real_distribution<float> xDist(-fieldWidth / 2.0f, fieldWidth / 2.0f);
	std::uniform_real_distribution<float> yDist(-fieldHeight / 2.0f, fieldHeight / 2.0f);
	std::normal_distribution<float> radDist(meanRadius, devRadius);
	std::normal_distribution<float> ratDist(meanRatio, devRatio);
	std::normal_distribution<float> flareDist(meanFlares, devFlares);
	std::normal_distribution<float> colorFreqDist(meanColorFreq, devColorFreq);
	std::uniform_real_distribution<float> phaseDist(0.0f, 2.0f * 3.14159f);
	std::normal_distribution<float> scaleAmplitudeDist(meanscaleAmplitude, devscaleAmplitude);
	std::normal_distribution<float> scaleFreqDist(meanColorFreq, devColorFreq);

	const Color colors[] = { Colors::Red, Colors::Green, Colors::Yellow, Colors::Blue, Colors::Cyan, Colors::White, Colors::Magenta };
	std::uniform_int_distribution<size_t> cDist(0, std::end(colors) - std::begin(colors));

	while (stars.size() < nStars)
	{
		const auto rad = std::clamp(radDist(rng), minRadius, maxRadius);
		const Vef2 pos = { xDist(rng), yDist(rng) };

		const auto scaleAmplitude = std::clamp(scaleAmplitudeDist(rng), minscaleAmplitude, maxscaleAmplitude);
		const float maxRad = rad * (1.0f + scaleAmplitude);

		if (std::any_of(stars.begin(), stars.end(), [&](const StarBro& sb) { return (sb.GetPos() - pos).Length() < sb.GetMaxRadius() + maxRad; }))
		{
			continue;
		}

		
		const auto ratio = std::clamp(ratDist(rng), minRatio, maxRatio);
		const auto flares = std::clamp((int)flareDist(rng), minnFlares, maxnFlares);

		const auto scaleFrequency = std::clamp(scaleFreqDist(rng), minscaleFreq, maxscaleFreq);
		const auto scalePhase = phaseDist(rng);

		const auto colorFreq = std::clamp(colorFreqDist(rng), minColorFreq, maxColorFreq);
		const auto colorPhase = phaseDist(rng);
		const Color c = colors[cDist(rng)];

		stars.emplace_back(rad, ratio, colorFreq, colorPhase, scaleAmplitude, scaleFrequency, scalePhase, pos, flares, c);
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
	camCtrl.Update();

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
		e.Update(dt);
	}
}

void Game::ComposeFrame()
{
	const RectF vp = cam.GetViewPort();
	for (auto& e : stars)
	{
		if (e.GetRect().IsOverLappingWith(vp))
		{
			cam.Draw(e.GetDrawable());
		}
	}
}

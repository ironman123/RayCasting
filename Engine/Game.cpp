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
#include <sstream>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	p(300,200)
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
	Mouse::Event readMouse = wnd.mouse.Read();
	if (readMouse.LeftIsPressed())
	{
		brd.ToggleCellStatus(brd.GetCell(wnd.mouse.GetPos()));
	}
	else if (wnd.kbd.KeyIsPressed('C'))
	{
		brd.ClearAllCells();
	}
}

void Game::ComposeFrame()
{
	brd.DrawCells(gfx);
	//for (int y = 0; y < Graphics::ScreenHeight; y += 90)
	//{
	//	for (int x = 0; x < Graphics::ScreenWidth; x += 90)
	//	{
	//		gfx.DrawLine(Vec2F((float)wnd.mouse.GetPos().x, (float)wnd.mouse.GetPos().y), Vec2F((float)x, (float)y), Colors::Red);
	//		gfx.DrawLine(Vec2F((float)wnd.mouse.GetPos().x, (float)wnd.mouse.GetPos().y), Vec2F((float)x, (float)y), Colors::Red);
	//	}
	//}

	//for (int x = 0; x < Graphics::ScreenWidth; x++)
	//{
	//	gfx.DrawLine(Vec2F((float)x, 0.0f), Vec2F((float)wnd.mouse.GetPos().x, (float)wnd.mouse.GetPos().y), Colors::Red);
	//}
	//for (int y = 0; y < Graphics::ScreenHeight; y++)
	//{
	//	gfx.DrawLine(Vec2F((float)wnd.mouse.GetPos().x, (float)wnd.mouse.GetPos().y), Vec2F(0.0f, (float)y), Colors::Red);
	//}

	
	//gfx.DrawLinedCircle(p, radius, Colors::Magenta);
	//if(wnd.mouse.RightIsPressed())
	ft.Start();
	gfx.DrawLinedCircle(Vec2(wnd.mouse.GetPos().x, wnd.mouse.GetPos().y), radius, Colors::Red);
	float dt = ft.Stop();
	std::ostringstream ss;
	ss << dt;
	std::string s(ss.str());
	OutputDebugStringA("time taken: ");
	OutputDebugStringA(s.c_str());
	OutputDebugStringA("\n");
	//gfx.DrawLineDDA(Vec2F(50.0f, 50.0f), Vec2F(wnd.mouse.GetPos().x, wnd.mouse.GetPos().y), Colors::Red);
	//gfx.DrawCircleOutline(Vec2(300, 200), 180, Colors::Blue);
	//brd.DrawGrid(gfx);
}

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
	bounds(Vef2{0.0f,0.0f},375.0f,275.0f),
	pE(pModel),
	sE(sModel)
{
	pModel.emplace_back(Vef2{ 50.0f,50.0f }, Vef2{ 52.0f,52.0f });
	pModel.emplace_back(Vef2{ 100.0f,50.0f }, Vef2{ 102.0f,52.0f });
	pModel.emplace_back(Vef2{ 100.0f,100.0f }, Vef2{ 102.0f,102.0f });
	pModel.emplace_back(Vef2{ 50.0f,100.0f }, Vef2{ 52.0f,102.0f });
	pE.SetModel(pModel);

	sModel.emplace_back(Stick{ pModel[0],pModel[1] });
	sModel.emplace_back(Stick{ pModel[1],pModel[2] });
	sModel.emplace_back(Stick{ pModel[2],pModel[3] });
	sModel.emplace_back(Stick{ pModel[3],pModel[0] });
	//sModel.emplace_back(Stick{ pModel[2],pModel[0] });
	sE.SetModel(sModel);
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

	UpdatePtEntity(dt, pE.GetPtrModel());

	sE.Update();
	UpdatePtEntity(dt, sE.GetPtModel());
	UpdateStEntity(dt, sE.GetStModel(), bounds);
	DoBoundaryCollision(sE.GetPtModel(), bounds);
	sE.Update();


	DoBoundaryCollision(pE.GetPtrModel(), bounds);
	//DoBoundaryCollision(sE.GetPtModel(), bounds);
}

void Game::ComposeFrame()
{
	cam.Draw(bounds.GetDrawable());
	cam.Draw(pE.GetDrawable());
	cam.Draw(sE.GetDrawable());
}

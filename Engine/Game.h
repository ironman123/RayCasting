/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <random>
#include "Board.h"
#include "FrameTimer.h"
#include "CoordinateTransformer.h"
#include "Entity.h"
#include "Camera.h"
#include "StarBro.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	std::mt19937 rng;
	std::random_device rd;

	static constexpr float fieldWidth = 10000.0f;
	static constexpr float fieldHeight = 6000.0f;
	static constexpr int nStars = 500;
	static constexpr float maxRadius = 300.0f;
	static constexpr float minRadius = 40.0f;
	static constexpr float meanRadius = 170.0f;
	static constexpr float devRadius = 90.0f;
	static constexpr float maxRatio = 0.75f;
	static constexpr float minRatio = 0.15f;
	static constexpr float meanRatio = 0.45f;
	static constexpr float devRatio = 0.25f;
	static constexpr float meanFlares = 6.5f;
	static constexpr float devFlares = 2.0f;
	static constexpr int maxnFlares = 10;
	static constexpr int minnFlares = 3;

	CoordinateTransformer ct;
	Camera cam;
	std::vector<StarBro> stars;

	/********************************/
};
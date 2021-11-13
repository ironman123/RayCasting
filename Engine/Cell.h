#pragma once
#include "Vec2.h"
#include "Graphics.h"

class Cell
{
public:
	//Cell(const Location& loc);
	void Draw(Graphics& gfx, const Vei2& loc)const;
	void DrawOutLine(Graphics& gfx, const Vei2& loc)const;
	void SetColor(Color c);
	bool ActiveStatus()const;
	void ToggleActive();
private:
	bool isActive = false;
	Vei2 loc;
	Color cellColor = Color{ 90,0,210 };
	Color outlineColor = Color{ 255,255,255 };
public:
	static constexpr int celldim = 20;
};
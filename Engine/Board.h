#pragma once
#include "Vec2.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Cell.h"

class Board
{
public:
	Board() = default;
	void DrawCells(Graphics& gfx)const;
	void DrawGrid(Graphics& gfx)const;
	bool IsInsideBoard(const Vec2& loc)const;
	void SetColorToCell(const Vec2& loc, Color c);
	void ToggleCellStatus(const Vec2& loc);
	void ClearAllCells();
	void GetCellStatus(const Vec2& loc)const;
	Vec2 GetCell(const Vec2& mouseLoc)const;
	int GetWidth()const;
	int GetHeight()const;
private:
	static constexpr int width = 40;
	static constexpr int height = 30;
	Cell cells[width * height];
};
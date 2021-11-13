#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Cell.h"

class Board
{
public:
	Board() = default;
	void DrawCells(Graphics& gfx)const;
	void DrawGrid(Graphics& gfx)const;
	bool IsInsideBoard(const Vei2& loc)const;
	void SetColorToCell(const Vei2& loc, Color c);
	void ToggleCellStatus(const Vei2& loc);
	void ClearAllCells();
	void GetCellStatus(const Vei2& loc)const;
	Vei2 GetCell(const Vei2& mouseLoc)const;
	int GetWidth()const;
	int GetHeight()const;
private:
	static constexpr int width = 40;
	static constexpr int height = 30;
	Cell cells[width * height];
};
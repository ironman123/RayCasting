#include "Board.h"
#include <assert.h>

void Board::DrawCells(Graphics& gfx)const
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			const Vei2 loc = { x,y };
			if (cells[x + (width * y)].ActiveStatus())
			{
				cells[x + (width * y)].Draw(gfx, loc);
			}
		}
	}
}

void Board::DrawGrid(Graphics& gfx) const
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			const Vei2 loc = { x,y };
			cells[x + (width * y)].DrawOutLine(gfx, loc);
		}
	}
}

bool Board::IsInsideBoard(const Vei2& loc) const
{
	return loc.x >= 0 && loc.x < width&& loc.y >= 0 && loc.y < height;
}

void Board::SetColorToCell(const Vei2& loc, Color c)
{
	cells[loc.x + (width * loc.y)].SetColor(c);
}

void Board::ToggleCellStatus(const Vei2& loc)
{
	cells[loc.x + (width * loc.y)].ToggleActive();
}

void Board::ClearAllCells()
{
	for each (Cell& c in cells)
	{
		if (c.ActiveStatus())
		{
			c.ToggleActive();
		}
	}
}

void Board::GetCellStatus(const Vei2& loc) const
{
	cells[loc.x + (width * loc.y)].ActiveStatus();
}

Vei2 Board::GetCell(const Vei2& mouseLoc) const
{
	return Vei2((mouseLoc.x) / Cell::celldim, (mouseLoc.y) / Cell::celldim);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}
#include "Cell.h"

//Cell::Cell(const Location& loc)
//	:
//	loc(loc)
//{
//}

void Cell::Draw(Graphics& gfx, const Vec2& loc) const
{
	gfx.DrawRectDim(loc.x * celldim, loc.y * celldim, celldim, celldim, cellColor);
}

void Cell::DrawOutLine(Graphics& gfx, const Vec2& loc) const
{
	gfx.DrawRectOutLine(loc.x * celldim, loc.y * celldim, celldim, celldim, outlineColor);
}

void Cell::SetColor(Color c_in)
{
	cellColor = c_in;
}

bool Cell::ActiveStatus() const
{
	return isActive;
}

void Cell::ToggleActive()
{
	//if (isActive)
	//{
	//	isActive = false;
	//}
	//else
	//{
	//	isActive = true;
	//}
	isActive ^= true;
}

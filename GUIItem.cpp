#include "GUIItem.h"

GUIItem::GUIItem(int x, int y, int maxX, int maxY) :
	x{ x },
	y{ y },
	maxX{ maxX },
	maxY{ maxY }
{
}

int GUIItem::GetX() noexcept
{
	if (x < 0)
		return (maxX + x);
	else
		return x;
}

int GUIItem::GetY() noexcept
{
	if (y < 0)
		return (maxY + y);
	else
		return y;
}
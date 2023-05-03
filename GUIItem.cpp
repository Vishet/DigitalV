#include "GUIItem.h"

GUIItem::GUIItem(int x, int y) :
	x{ x },
	y{ y }
{
}

int GUIItem::GetX() const noexcept
{
	return x;
}

int GUIItem::GetY() const noexcept
{
	return y;
}

void GUIItem::KeyInput(const Keyboard::Event& keyEvent) noexcept
{

}

void GUIItem::MouseInput(const Mouse::Event& mouseEvent) noexcept
{
}

#include "NANDGUIObject.h"
#include "Graphics.h"
#include "NANDChip.h"

NANDGUIObject::NANDGUIObject(float x, float y) :
	GUIChip(x, y)
{

}

void NANDGUIObject::Draw()
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		1.0f, 1.0f, 1.0f
	);

	graphics->DrawCenteredText(
		L"AND",
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		0.0f, 0.0f, 1.0f
	);
}

bool NANDGUIObject::IsColliding(float x, float y) noexcept
{
	if (
		x >= GetX() - width / 2 &&
		x <= GetX() + width / 2 &&
		y >= GetY() - height / 2 &&
		y <= GetY() + height / 2
		)
		return true;
	else
		return false;
}

Chip* NANDGUIObject::GetChip() noexcept
{
	return new NANDChip(x, y);
}

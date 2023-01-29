#include "NANDGUIObject.h"
#include "Graphics.h"
#include "NANDChip.h"

NANDGUIObject::NANDGUIObject(float x, float y) :
	x{ x },
	y{ y }
{

}

void NANDGUIObject::Draw()
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		x - width / 2, y - height / 2, 
		x + width / 2, y + height / 2,
		1.0f, 1.0f, 1.0f
	);

	graphics->DrawCenteredText(
		L"AND",
		x - width / 2, y - height / 2, 
		x + width / 2, y + height / 2,
		0.0f, 0.0f, 1.0f
	);
}

bool NANDGUIObject::IsColliding(float x, float y) noexcept
{
	if (
		x >= this->x - width / 2 &&
		x <= this->x + width / 2 &&
		y >= this->y - height / 2 &&
		y <= this->y + height / 2
		)
		return true;
	else
		return false;
}

Chip* NANDGUIObject::GetChip() noexcept
{
	return new NANDChip(x, y);
}

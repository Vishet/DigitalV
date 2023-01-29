#include "NANDChip.h"
#include "Graphics.h"

NANDChip::NANDChip(float x, float y) :
	Chip(x, y)
{
}

void NANDChip::Draw()
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		1.0f, 0.0f, 0.0f
	);

	graphics->DrawCenteredText(
		L"AND",
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		0.0f, 0.0f, 1.0f
	);
}

bool NANDChip::IsColliding(float x, float y)
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

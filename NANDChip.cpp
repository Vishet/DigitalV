#include "NANDChip.h"
#include "Graphics.h"

NANDChip::NANDChip(float x, float y) :
	x{ x },
	y{ y }
{
}

void NANDChip::Draw()
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		x - width / 2, y - height / 2,
		x + width / 2, y + height / 2,
		1.0f, 0.0f, 0.0f
	);

	graphics->DrawCenteredText(
		L"AND",
		x - width / 2, y - height / 2,
		x + width / 2, y + height / 2,
		0.0f, 0.0f, 1.0f
	);
}

bool NANDChip::IsColliding(float x, float y)
{
	if (
		x >= x - width / 2 &&
		x <= x + width / 2 &&
		y >= y - height / 2 &&
		y <= y + height / 2
		)
		return true;
	else
		return false;
}

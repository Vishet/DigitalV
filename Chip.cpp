#include "Chip.h"
#include "Graphics.h"

Chip::Chip(float x, float y, const std::wstring& label) :
	Object(x, y),
	label{ label }
{
}

void Chip::Draw()
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		1.0f, 1.0f, 1.0f
	);

	graphics->DrawCenteredText(
		label.c_str(),
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		0.0f, 0.0f, 1.0f
	);
}

bool Chip::IsColliding(float x, float y)
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
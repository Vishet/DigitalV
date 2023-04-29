#include "NANDChipItem.h"

#include "Graphics.h"

NANDChipItem::NANDChipItem(int x, int y, int maxX, int maxY) :
	GUIItem(x, y, maxX, maxY)
{
}

void NANDChipItem::Draw()
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		static_cast<float>(GetX() - width / 2), static_cast<float>(GetY() - height / 2),
		static_cast<float>(GetX() + width / 2), static_cast<float>(GetY() + height / 2),
		r, g, b
	);

	graphics->DrawCenteredText(
		label.data(),
		static_cast<float>(GetX() - width / 2), static_cast<float>(GetY() - height / 2),
		static_cast<float>(GetX() + width / 2), static_cast<float>(GetY() + height / 2),
		textR, textG, textB
	);

	graphics->FillCircle(
		static_cast<float>(GetX() + inputXOffset), static_cast<float>(GetY() - inputYOffset),
		static_cast<float>(ioRadius),
		ioR, ioG, ioB
	);
	graphics->FillCircle(
		static_cast<float>(GetX() + inputXOffset), static_cast<float>(GetY() + inputYOffset),
		static_cast<float>(ioRadius),
		ioR, ioG, ioB
	);

	graphics->FillCircle(
		static_cast<float>(GetX() + outputXOffset), static_cast<float>(GetY() + outputYOffset),
		static_cast<float>(ioRadius),
		ioR, ioG, ioB
	);
}



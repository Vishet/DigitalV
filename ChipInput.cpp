#include "ChipInput.h"
#include "Graphics.h"
#include "Chip.h"

ChipInput::ChipInput(float chipX, float chipY, float xOffset, float yOffset, bool state) :
	Object(chipX + xOffset, chipY + yOffset),
	state{ state },
	xOffset{ xOffset },
	yOffset{ yOffset }
{
}

ChipInput::ChipInput(const ChipInput& chipInput)  :
	Object(chipInput)
{
	state = chipInput.state;
	xOffset = chipInput.xOffset;
	yOffset = chipInput.yOffset;
}

void ChipInput::SetState(bool state) noexcept
{
	this->state = state;

}

void ChipInput::Draw()
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	graphics->FillCircle(GetX(), GetY(), radius, r, g, b);
}

void ChipInput::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x + xOffset, y + yOffset);
}
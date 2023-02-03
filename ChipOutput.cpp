#include "ChipOutput.h"
#include "Graphics.h"

ChipOutput::ChipOutput(float chipX, float chipY, float xOffset, float yOffset, bool state) :
	Object(chipX + xOffset, chipY + yOffset, LayerIndex::NONE),
	state{ state },
	xOffset{ xOffset },
	yOffset{ yOffset }
{
}

ChipOutput::ChipOutput(const ChipOutput& chipInput) :
	Object(chipInput)
{
	state = chipInput.state;
	xOffset = chipInput.xOffset;
	yOffset = chipInput.yOffset;
}

void ChipOutput::SetState(bool state) noexcept
{
	this->state = state;
}

void ChipOutput::Draw()
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	graphics->FillCircle(GetX(), GetY(), radius, r, g, b);
}

void ChipOutput::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x + xOffset, y + yOffset);
}

CollisionType ChipOutput::IsColliding(float x, float y)
{
	float distance = static_cast<float>(sqrt(pow(GetX() - x, 2) + pow(GetY() - y, 2)));
	if (distance <= radius)
		return CollisionType::CHIPOUTPUT;
	else
		return CollisionType::NO_COLLISION;
}
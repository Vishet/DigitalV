#include "ChipOutput.h"
#include "Graphics.h"

ChipOutput::ChipOutput(float chipX, float chipY, float xOffset, float yOffset, bool state) :
	Object(chipX + xOffset, chipY + yOffset, LayerIndex::NONE),
	state{ state },
	xOffset{ xOffset },
	yOffset{ yOffset }
{
}

ChipOutput::ChipOutput(const ChipOutput& chipOutput) :
	Object(chipOutput),
	state{ chipOutput.state },
	xOffset{ chipOutput.xOffset },
	yOffset{ chipOutput.yOffset }
{
}

ChipOutput::ChipOutput(const ChipOutput&& chipOutput) :
	Object(std::move(chipOutput)),
	state{ chipOutput.state },
	xOffset{ chipOutput.xOffset },
	yOffset{ chipOutput.yOffset }
{
}

void ChipOutput::SetState(bool state) noexcept
{
	this->state = state;
}

void ChipOutput::Draw() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	graphics->FillCircle(GetX(), GetY(), radius, r, g, b);
}

void ChipOutput::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x + xOffset, y + yOffset);
}

Collision ChipOutput::IsColliding(float x, float y)
{
	Collision collision{x, y, CollisionType::NO_COLLISION, this};

	float distance = static_cast<float>(sqrt(pow(GetX() - x, 2) + pow(GetY() - y, 2)));
	if (distance <= radius)
		collision.type = CollisionType::CHIPOUTPUT;

	return collision;
}
#include "ChipInput.h"
#include "Graphics.h"
#include "Chip.h"
#include "LayersIndexes.h"

ChipInput::ChipInput(float chipX, float chipY, float xOffset, float yOffset, bool state) :
	Object(chipX + xOffset, chipY + yOffset, LayerIndex::NONE),
	state{ state },
	xOffset{ xOffset },
	yOffset{ yOffset }
{
}

ChipInput::ChipInput(const ChipInput& chipInput)  :
	Object(chipInput),
	state{ chipInput.state },
	xOffset{ chipInput.xOffset },
	yOffset{ chipInput.yOffset }
{
}

ChipInput::ChipInput(const ChipInput&& chipInput) :
	Object(std::move(chipInput)),
	state{ chipInput.state },
	xOffset{ chipInput.xOffset },
	yOffset{ chipInput.yOffset }
{
}

void ChipInput::SetState(bool state) noexcept
{
	this->state = state;
}

void ChipInput::Draw() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	graphics->FillCircle(GetX(), GetY(), radius, r, g, b);
}

void ChipInput::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x + xOffset, y + yOffset);
	if(connectedWire)
		connectedWire->SetPosition(GetX(), GetY());
}

Collision ChipInput::IsColliding(float x, float y)
{
	Collision collision{ x, y, CollisionType::NO_COLLISION, this };

	float distance = static_cast<float>(sqrt(pow(GetX() - x, 2) + pow(GetY() - y, 2)));
	if (distance <= radius)
		collision.type = CollisionType::CHIPINPUT;

	return collision;
}
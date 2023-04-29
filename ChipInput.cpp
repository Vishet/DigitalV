#include "ChipInput.h"
#include "Graphics.h"
#include "Chip.h"
#include "LayersIndexes.h"
#include "Chip.h"

ChipInput::ChipInput(
	Chip* parentChip,
	float chipX, float chipY, 
	float xOffset, float yOffset, 
	float radius,
	float rOff, float gOff, float bOff,
	float rOn, float gOn, float bOn,
	float aOff, float aOn
) :
	Object(chipX + xOffset, chipY + yOffset, LayerIndex::NONE),
	parentChip{ parentChip },
	xOffset{ xOffset },
	yOffset{ yOffset },
	radius{ radius },
	rOff{ rOff }, gOff{ gOff }, bOff{ bOff },
	rOn{ rOn }, gOn{ gOn }, bOn{ bOn },
	aOff{ aOff }, aOn{ aOn }
{
}

ChipInput::ChipInput(const ChipInput& chipInput) :
	Object(chipInput),
	parentChip{ chipInput.parentChip },
	xOffset{ chipInput.xOffset },
	yOffset{ chipInput.yOffset },
	radius{ chipInput.radius },
	rOff{ chipInput.rOff }, gOff{ chipInput.gOff }, bOff{ chipInput.bOff },
	rOn{ chipInput.rOn }, gOn{ chipInput.gOn }, bOn{ chipInput.bOn },
	aOff{ chipInput.aOff }, aOn{ chipInput.aOn }
{
}

ChipInput::ChipInput(const ChipInput&& chipInput) noexcept :
	Object(chipInput),
	parentChip{ chipInput.parentChip },
	xOffset{ chipInput.xOffset },
	yOffset{ chipInput.yOffset },
	radius{ chipInput.radius },
	rOff{ chipInput.rOff }, gOff{ chipInput.gOff }, bOff{ chipInput.bOff },
	rOn{ chipInput.rOn }, gOn{ chipInput.gOn }, bOn{ chipInput.bOn },
	aOff{ chipInput.aOff }, aOn{ chipInput.aOn }
{
}

void ChipInput::SetState(bool state) noexcept
{
	this->state = state;
	parentChip->UpdateOutput();
}

void ChipInput::Draw() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	if (state)
		graphics->FillCircle(GetX(), GetY(), radius, rOn, gOn, bOn);
	else
		graphics->FillCircle(GetX(), GetY(), radius, rOff, gOff, bOff);
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

void ChipInput::ConnectWire(Wire* wire) noexcept
{
	this->connectedWire = wire;
	if (wire)
		this->SetState(wire->GetState());
	else
		this->SetState(false);
}
#include "ChipOutput.h"
#include "Graphics.h"

ChipOutput::ChipOutput(
	float chipX, float chipY,
	float xOffset, float yOffset,
	float radius,
	float rOff, float gOff, float bOff,
	float rOn, float gOn, float bOn,
	float aOff, float aOn
) :
	Object(chipX + xOffset, chipY + yOffset, LayerIndex::NONE),
	xOffset{ xOffset },
	yOffset{ yOffset },
	radius{ radius },
	rOff{ rOff }, gOff{ gOff }, bOff{ bOff },
	rOn{ rOn }, gOn{ gOn }, bOn{ bOn },
	aOff{ aOff }, aOn{ aOn }
{
}

ChipOutput::ChipOutput(const ChipOutput& chipOutput) :
	Object(chipOutput),
	xOffset{ chipOutput.xOffset },
	yOffset{ chipOutput.yOffset },
	radius{ chipOutput.radius },
	rOff{ chipOutput.rOff }, gOff{ chipOutput.gOff }, bOff{ chipOutput.bOff },
	rOn{ chipOutput.rOn }, gOn{ chipOutput.gOn }, bOn{ chipOutput.bOn },
	aOff{ chipOutput.aOff }, aOn{ chipOutput.aOn }
{
}

ChipOutput::ChipOutput(const ChipOutput&& chipOutput) noexcept :
	Object(chipOutput),
	xOffset{ chipOutput.xOffset },
	yOffset{ chipOutput.yOffset },
	radius{ chipOutput.radius },
	rOff{ chipOutput.rOff }, gOff{ chipOutput.gOff }, bOff{ chipOutput.bOff },
	rOn{ chipOutput.rOn }, gOn{ chipOutput.gOn }, bOn{ chipOutput.bOn },
	aOff{ chipOutput.aOff }, aOn{ chipOutput.aOn }
{
}

void ChipOutput::SetState(bool state) noexcept
{
	this->state = state;

	if (connectedWire)
		connectedWire->UpdateState();
}

void ChipOutput::Draw() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	if(state)
		graphics->FillCircle(GetX(), GetY(), radius, rOn, gOn, bOn);
	else
		graphics->FillCircle(GetX(), GetY(), radius, rOff, gOff, bOff);
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
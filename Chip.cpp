#include "Chip.h"
#include "Graphics.h"
#include "LayersIndexes.h"

Chip::Chip(float x, float y, float width, float height, const std::wstring& label) :
	Object(x, y, LayerIndex::CHIPS),
	label{ label },
	width{ width },
	height{ height }
{
	this->UpdateOutput();
	this->Reset();
}

Chip::Chip(const Chip& chip) :
	Object(chip)
{
	width = chip.width;
	height = chip.height;
	label = chip.label;

	
	for (const auto& sourceInput : chip.inputs)
	{
		inputs.emplace_back(sourceInput);
		inputs.back().SetParentChip(this);
	}
	for (const auto& sourceOutput : chip.outputs)
	{
		outputs.emplace_back(sourceOutput);
	}
}

Object* Chip::Clone()
{
	auto chipClone{ new Chip(*this) };
	chipClone->UpdateOutput();
	return chipClone;
}

Chip::~Chip()
{
}

void Chip::Draw() const
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		1.0f, 1.0f, 1.0f
	);

	graphics->DrawCenteredText(
		label,
		GetX() - width / 2, GetY() - height / 2,
		GetX() + width / 2, GetY() + height / 2,
		0.0f, 0.0f, 1.0f
	);

	for (const auto& input : inputs)
		input.Draw();

	for (const auto& output : outputs)
		output.Draw();
}

Collision Chip::IsColliding(float x, float y)
{
	Collision collision{x, y, CollisionType::NO_COLLISION, this};

	for (auto& input : inputs)
	{
		Collision inputCollision{ input.IsColliding(x, y) };
		if (inputCollision.type != CollisionType::NO_COLLISION)
			return inputCollision;
	}

	for (auto& output : outputs)
	{
		Collision outputCollision{ output.IsColliding(x, y) };
		if (outputCollision.type != CollisionType::NO_COLLISION)
			return outputCollision;
	}

	if (
		x >= GetX() - width / 2 &&
		x <= GetX() + width / 2 &&
		y >= GetY() - height / 2 &&
		y <= GetY() + height / 2
		)
	{
		if (GetLayerIndex() == LayerIndex::CHIPS)
			collision.type = CollisionType::CHIP;
		else if (GetLayerIndex() == LayerIndex::PALLETE)
			collision.type = CollisionType::PALLETE;
	}

	return collision;
}

void Chip::AddInput(
	float xOffset, float yOffset,
	float radius,
	float rOff, float gOff, float bOff,
	float rOn, float gOn, float bOn,
	float aOff, float aOn
) noexcept
{
	inputs.emplace_back(
		ChipInput(
			this,
			GetX(), GetY(), xOffset, yOffset, radius,
			rOff, gOff, bOff,
			rOn, gOn, bOn,
			aOff, aOn
		)
	);
}

void Chip::AddOutput(
	float xOffset, float yOffset,
	float radius,
	float rOff, float gOff, float bOff,
	float rOn, float gOn, float bOn,
	float aOff, float aOn
) noexcept
{
	outputs.emplace_back(
		ChipOutput(
			GetX(), GetY(), xOffset, yOffset, radius,
			rOff, gOff, bOff,
			rOn, gOn, bOn,
			aOff, aOn
		)
	);
}

void Chip::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x, y);

	for (auto& input : inputs)
		input.SetPosition(x, y);

	for (auto& output : outputs)
		output.SetPosition(x, y);
}

void Chip::UpdateOutput() noexcept
{
	if (!alreadyProcessed)
	{
		alreadyProcessed = true;
	}
}

void Chip::Reset() noexcept
{
	alreadyProcessed = false;
}

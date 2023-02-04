#include "Chip.h"
#include "Graphics.h"
#include "LayersIndexes.h"

Chip::Chip(float x, float y, float width, float height, const std::wstring& label) :
	Object(x, y, LayerIndex::CHIPS),
	label{ label },
	width{ width },
	height{ height }
{
}

Chip::Chip(const Chip& chip) :
	Object(chip)
{
	width = chip.width;
	height = chip.height;
	label = chip.label;
	
	for (const auto& sourceInput : chip.inputs)
	{
		AddInput(sourceInput.GetXOffset(), sourceInput.GetYOffset());
	}
	for (const auto& sourceOutput : chip.outputs)
	{
		AddInput(sourceOutput.GetXOffset(), sourceOutput.GetYOffset());
	}
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
		label.c_str(),
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

void Chip::AddInput(float xOffset, float yOffset) noexcept
{
	inputs.emplace_back(ChipInput(GetX(), GetY(), xOffset, yOffset));
}

void Chip::AddOutput(float xOffset, float yOffset) noexcept
{
	outputs.emplace_back(ChipOutput(GetX(), GetY(), xOffset, yOffset));
}

void Chip::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x, y);

	for (auto& input : inputs)
		input.SetPosition(x, y);
	for (auto output : outputs)
		output.SetPosition(x, y);
}

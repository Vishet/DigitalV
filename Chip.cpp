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
	
	for (auto sourceInput : chip.inputs)
	{
		AddInput(sourceInput->GetXOffset(), sourceInput->GetYOffset());
	}
	for (auto sourceOutput : chip.outputs)
	{
		AddInput(sourceOutput->GetXOffset(), sourceOutput->GetYOffset());
	}
}

Chip::~Chip()
{
	for (auto input : inputs)
	{
		delete input;
	}
	for (auto output : outputs)
	{
		delete output;
	}
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

	for (auto input : inputs)
		input->Draw();

	for (auto output : outputs)
		output->Draw();
}

CollisionType Chip::IsColliding(float x, float y)
{
	for (const auto input : inputs)
	{
		CollisionType inputCollisionType{ input->IsColliding(x, y) };
		if (inputCollisionType != CollisionType::NO_COLLISION)
			return inputCollisionType;
	}

	for (const auto output : outputs)
	{
		CollisionType outputsCollisionType{ output->IsColliding(x, y) };
		if (outputsCollisionType != CollisionType::NO_COLLISION)
			return outputsCollisionType;
	}

	if (
		x >= GetX() - width / 2 &&
		x <= GetX() + width / 2 &&
		y >= GetY() - height / 2 &&
		y <= GetY() + height / 2
		)
	{
		if (GetLayerIndex() == LayerIndex::CHIPS)
			return CollisionType::CHIP;
		else if (GetLayerIndex() == LayerIndex::PALLETE)
			return CollisionType::PALLETE;
		else
			return CollisionType::NO_COLLISION;
	}
	else
		return CollisionType::NO_COLLISION;
}

void Chip::AddInput(float xOffset, float yOffset) noexcept
{
	inputs.push_back(new ChipInput(GetX(), GetY(), xOffset, yOffset));
}

void Chip::AddOutput(float xOffset, float yOffset) noexcept
{
	outputs.push_back(new ChipOutput(GetX(), GetY(), xOffset, yOffset));
}

void Chip::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x, y);

	for (auto input : inputs)
		input->SetPosition(x, y);
	for (auto output : outputs)
		output->SetPosition(x, y);
}

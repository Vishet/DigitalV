#include "SimulationScene.h"

#include "Chip.h"
#include "ToggleSwitch.h"

void SimulationScene::Load()
{
	Chip* NANDChip{ new Chip(150.0f, 632.5f, 200.0f, 75.0f, L"NAND") };
	NANDChip->AddInput(-100.0f, 30.0f);
	NANDChip->AddInput(-100.0f, -30.0f);
	AddObject(Layer::GUI_CHIPS, NANDChip);

	ToggleSwitch* toggleSwitch{ new ToggleSwitch(400.0f, 632.5f, 50.0f, 1.0f, 0.0f, 0.0f, 0.5f) };
	AddObject(Layer::GUI_TOGGLES, toggleSwitch);
}

void SimulationScene::KeyInput(const Keyboard::Event& keyEvent) noexcept
{
	
}

void SimulationScene::MouseInput(const Mouse::Event& mouseEvent) noexcept
{
	auto eventType{ mouseEvent.GetType() };

	if (eventType == Mouse::Event::Type::LMBPressed)
	{
		int mouseX{ mouseEvent.GetX() };
		int mouseY{ mouseEvent.GetY() };

		SelectChip(mouseX, mouseY);
	}
	else if (eventType == Mouse::Event::Type::LMBReleased)
	{
		DropSelectedChip();
	}
}

void SimulationScene::Update()
{
	if (mouse->IsLMBDown())
	{
		DragSelectedChip();
	}
}

bool SimulationScene::IsPointInRect(
	float x, float y, 
	float rectX, float rectY, float rectX2, float rectY2
) const noexcept
{
	if (x >= rectX && x <= rectX2 && y >= rectY && y <= rectY2)
		return true;
	else
		return false;
}

Chip* SimulationScene::GetClickedChip(float x, float y) noexcept
{
	auto guiLayer{ GetLayerVector(GUI_CHIPS) };
	for (const auto& object : *guiLayer)
	{
		auto guiChip{ dynamic_cast<Chip*>(object) };
		if (guiChip->IsColliding(x, y))
			return new Chip(*guiChip);
	}

	auto circuitLayer{ GetLayerVector(CIRCUIT) };
	for (auto it{ circuitLayer->rbegin() }; it != circuitLayer->rend(); ++it)
	{
		auto chip{ dynamic_cast<Chip*>(*it) };
		if (chip->IsColliding(x, y))
			return chip;
	}

	return nullptr;
}

void SimulationScene::SelectChip(int mouseX, int mouseY) noexcept
{
	Chip* chip{ GetClickedChip(static_cast<float>(mouseX), static_cast<float>(mouseY)) };
	if (chip)
	{
		if (chip->IsInLayer())
			MoveObjectLayer(chip->GetLayerIndex(), GetObjectIndex(CIRCUIT, chip), SELECTED_CHIP);
		else
		{
			AddObject(SELECTED_CHIP, chip);
		}
	}
}

void SimulationScene::DropSelectedChip() noexcept
{
	auto selectedChipLayer{ GetLayerVector(Layer::SELECTED_CHIP) };
	if (!selectedChipLayer->empty())
	{
		MoveObjectLayer(Layer::SELECTED_CHIP, 0, Layer::CIRCUIT);
	}
}

void SimulationScene::DragSelectedChip() noexcept
{
	const LayerVector* selectedChipLayer{ GetLayerVector(Layer::SELECTED_CHIP) };
	if (!selectedChipLayer->empty())
	{
		Object* selectedChip{ selectedChipLayer->front() };
		selectedChip->SetPosition(
			static_cast<float>(mouse->GetLimitedX()),
			static_cast<float>(mouse->GetLimitedY())
		);
	}
}

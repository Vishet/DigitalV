#include "SimulationScene.h"

#include "NANDGUIObject.h"
#include "NANDChip.h"

void SimulationScene::Load()
{
	AddObject(Layer::GUI_CHIPS, new NANDGUIObject(150.0f, 632.5f));
}

void SimulationScene::KeyInput(const Keyboard::Event& keyEvent) noexcept
{
	
}

void SimulationScene::MouseInput(const Mouse::Event& mouseEvent) noexcept
{
	auto eventType{ mouseEvent.GetType() };

	if (eventType == Mouse::Event::Type::LMBPressed)
	{
		float mouseX{ static_cast<float>(mouseEvent.GetX()) };
		float mouseY{ static_cast<float>(mouseEvent.GetY()) };
		Chip* chip{ GetClickedGUIChip(mouseX, mouseY) };
		if (chip)
		{
			AddObject(Layer::SELECTED_CHIP, chip);
		}
	}
	else if (eventType == Mouse::Event::Type::LMBReleased)
	{
		auto selectedChipLayer{ GetLayerVector(Layer::SELECTED_CHIP) };
		if (!selectedChipLayer->empty())
		{
			MoveObjectLayer(Layer::SELECTED_CHIP, 0, Layer::CIRCUIT);
		}
	}
}

void SimulationScene::Update()
{
	if (mouse->IsLMBDown())
	{
		const LayerVector* selectedChipLayer{ GetLayerVector(Layer::SELECTED_CHIP) };
		if(!selectedChipLayer->empty()) 
		{
			Object* selectedChip{ selectedChipLayer->front() };
			selectedChip->SetPosition(mouse->GetX(), mouse->GetY());
		}
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

Chip* SimulationScene::GetClickedGUIChip(float x, float y) noexcept
{
	auto guiLayer{ GetLayerVector(GUI_CHIPS) };
	for (const auto& object : *guiLayer)
	{
		auto guiChip{ dynamic_cast<NANDGUIObject*>(object) };
		if(guiChip->IsColliding(x, y))
			return guiChip->GetChip();
	}

	return nullptr;
}

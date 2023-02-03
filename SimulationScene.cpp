#include "SimulationScene.h"

#include "Chip.h"
#include "ToggleSwitch.h"
#include "LayersIndexes.h"

void SimulationScene::Load()
{
	Chip* NANDChip{ new Chip(150.0f, 632.5f, 200.0f, 75.0f, L"NAND") };
	NANDChip->AddInput(-100.0f, 30.0f);
	NANDChip->AddInput(-100.0f, -30.0f);
	NANDChip->AddOutput(100.0f, 0.0f);
	AddObject(LayerIndex::PALLETE, NANDChip);

	ToggleSwitch* toggleSwitch{ new ToggleSwitch(400.0f, 632.5f, 50.0f, 1.0f, 0.0f, 0.0f, 0.5f) };
	AddObject(LayerIndex::PALLETE, toggleSwitch);
}

void SimulationScene::KeyInput(const Keyboard::Event& keyEvent) noexcept
{
	
}

void SimulationScene::MouseInput(const Mouse::Event& mouseEvent) noexcept
{
	auto eventType{ mouseEvent.GetType() };

	int mouseX{ mouseEvent.GetX() };
	int mouseY{ mouseEvent.GetY() };

	switch (eventType)
	{

	case Mouse::Event::Type::LMBPressed:
	{
		ClickEvent clickEvent{ GetCollidedObject(mouseX, mouseY) };
		switch (clickEvent.type)
		{

		case CollisionType::PALLETE:
		{
			SelectPalleteObject(clickEvent.object);
			break;
		}

		case CollisionType::TOGGLE:
		case CollisionType::CHIP:
		{
			SelectCircuitObject(clickEvent.object);
			break;
		}

		}
			break;
	}

		case Mouse::Event::Type::LMBReleased:
		{
			DropSelectedObject();
			break;
		}

		case Mouse::Event::Type::RMBPressed:
		{
			ClickEvent clickEvent{ GetCollidedObject(mouseX, mouseY) };
			switch (clickEvent.type)
			{

			case CollisionType::TOGGLE:
			{
				ToggleSwitches(mouseX, mouseY);
				break;
			}

			}
			
			break;
		}
	}
}

void SimulationScene::Update()
{
	if (mouse->IsLMBDown())
	{
		DragSelectedObject();
	}
}

void SimulationScene::SelectPalleteObject(Object* palleteObject) noexcept
{
	AddObject(SELECTED_OBJECT, palleteObject->Clone());
}

void SimulationScene::DragSelectedObject() noexcept
{
	const LayerVector* selectedObjectLayer{ GetLayerVector(LayerIndex::SELECTED_OBJECT) };
	if (!selectedObjectLayer->empty())
	{
		Object* selectedObject{ selectedObjectLayer->front() };
		selectedObject->SetPosition(
			static_cast<float>(mouse->GetLimitedX()),
			static_cast<float>(mouse->GetLimitedY())
		);
	}
}

void SimulationScene::DropSelectedObject() noexcept
{
	auto selectedObjectLayer{ GetLayerVector(LayerIndex::SELECTED_OBJECT) };
	if (!selectedObjectLayer->empty())
	{
		Object* selectedObject{ GetObject(LayerIndex::SELECTED_OBJECT, 0) };
		LayerIndex objectOriginalLayer{ selectedObject->GetOriginalLayerIndex() };
		MoveObjectLayer(LayerIndex::SELECTED_OBJECT, 0, objectOriginalLayer);
	}
}

void SimulationScene::SelectCircuitObject(Object* circuitObject) noexcept
{
	LayerIndex objectLayerIndex{ circuitObject->GetLayerIndex() };
	MoveObjectLayer(
		circuitObject->GetLayerIndex(),
		GetObjectIndex(objectLayerIndex, circuitObject),
		LayerIndex::SELECTED_OBJECT
	);
}

void SimulationScene::ToggleSwitches(int mouseX, int mouseY) noexcept
{
	const LayerVector* togglesLayer{ GetLayerVector(LayerIndex::TOGGLES) };

	for (auto it{ togglesLayer->rbegin() }; it != togglesLayer->rend(); ++it)
	{
		ToggleSwitch* toggleSwitch{ dynamic_cast<ToggleSwitch*>(*it) };
		if (toggleSwitch->IsColliding(
			static_cast<float>(mouseX), 
			static_cast<float>(mouseY)
		) != CollisionType::NO_COLLISION )
		{
			toggleSwitch->ToggleState();
			break;
		}
	}
}
#include "SimulationScene.h"

#include "Chip.h"
#include "ToggleSwitch.h"
#include "LayersIndexes.h"
#include "Wire.h"
#include "NANDChip.h"
#include "ChipPalleteGUI.h"

void SimulationScene::Load()
{
	LoadGUI(new ChipPalleteGUI());

	/*
	NANDChip* nandChip{ new NANDChip(150.0f, 632.5f, L"NAND") };
	AddObject(LayerIndex::PALLETE, nandChip);

	ToggleSwitch* toggleSwitch{ new ToggleSwitch(400.0f, 632.5f, 25.0f, 5.0f, 0.0f, 0.0f, 0.5f) };
	AddObject(LayerIndex::PALLETE, toggleSwitch);
	*/
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
		Collision clickCollision{ GetCollidedObject(mouseX, mouseY) };
		switch (clickCollision.type)
		{

		case CollisionType::PALLETE:
		{
			SelectPalleteObject(clickCollision.trigger);
			break;
		}

		case CollisionType::TOGGLE:
		case CollisionType::CHIP:
		{
			SelectCircuitObject(clickCollision.trigger);
			break;
		}

		case CollisionType::CHIPOUTPUT:
		{
			auto chipOutput{ dynamic_cast<ChipOutput*>(clickCollision.trigger) };

			Wire* connectedWire{ chipOutput->GetConnectedWire() };
			if (connectedWire)
			{
				connectedWire->SetInput(nullptr);
				connectedWire->SetPosition(static_cast<float>(mouseX), static_cast<float>(mouseY));
				MoveObjectLayer(connectedWire, LayerIndex::SELECTED_OBJECT);
			}
			else
				AddWire(chipOutput);

			break;
		}

		}
			break;
	}

	case Mouse::Event::Type::LMBReleased:
	{
		Collision clickCollision{ GetCollidedObject(mouseX, mouseY) };
		switch (clickCollision.type)
		{

		case CollisionType::CHIPINPUT:
		{
			Object* selectedObject{ GetObject(LayerIndex::SELECTED_OBJECT, 0) };
			if (selectedObject && selectedObject->GetOriginalLayerIndex() == LayerIndex::WIRES)
			{
				auto chipInput{ dynamic_cast<ChipInput*>(clickCollision.trigger) };
				DropSelectedWire(
					dynamic_cast<Wire*>(selectedObject),
					chipInput
				);
			}
				
			break;
		}

		default:
		{
			Object* selectedObject{ GetObject(LayerIndex::SELECTED_OBJECT, 0) };
			if (selectedObject)
			{
				if (selectedObject->GetOriginalLayerIndex() == LayerIndex::WIRES)
				{
					Wire* selectedWire{ dynamic_cast<Wire*>(selectedObject) };
					DeleteObject(selectedWire->GetLayerIndex(), 0);
					delete selectedWire;
				}			
				else
					DropSelectedObject();
			}		
		}

		}
		
		break;
	}

	case Mouse::Event::Type::RMBPressed:
	{
		Collision clickCollision{ GetCollidedObject(mouseX, mouseY) };
		switch (clickCollision.type)
		{

		case CollisionType::TOGGLE:
		{
			dynamic_cast<ToggleSwitch*>(clickCollision.trigger)->ToggleState();
			ResetChips();
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

Object* SimulationScene::GetSelectedObject() const noexcept
{
	auto selectedObjectLayer{ GetLayerVector(LayerIndex::SELECTED_OBJECT) };
	if (!selectedObjectLayer->empty())
	{
		return GetObject(LayerIndex::SELECTED_OBJECT, 0);
	}

	return nullptr;
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
	Object* selectedObject{ GetObject(LayerIndex::SELECTED_OBJECT, 0) };
	if (selectedObject)
	{
		LayerIndex objectOriginalLayer{ selectedObject->GetOriginalLayerIndex() };
		MoveObjectLayer(LayerIndex::SELECTED_OBJECT, 0, objectOriginalLayer);
	}
}

void SimulationScene::SelectCircuitObject(Object* circuitObject) noexcept
{
	MoveObjectLayer(circuitObject, LayerIndex::SELECTED_OBJECT);
}

void SimulationScene::AddWire(ChipOutput* output) noexcept
{
	Wire* wire{ 
		new Wire(
			output, 2.0f, output->GetState(), 
			0.5f, 0.5f, 0.5f, 
			0.0f, 0.0f, 0.5f
		) 
	};
	AddObject(LayerIndex::SELECTED_OBJECT, wire);
}

void SimulationScene::DropSelectedWire(Wire* selectedWire, ChipInput* chipInput) noexcept
{
	MoveObjectLayer(LayerIndex::SELECTED_OBJECT, 0, selectedWire->GetOriginalLayerIndex());
	selectedWire->SetInput(chipInput);
}

void SimulationScene::ResetChips() noexcept
{
	auto chipsLayer{ GetLayerVector(LayerIndex::CHIPS) };
	for(auto object : *chipsLayer)
	{
		Chip* chip{ dynamic_cast<Chip*>(object) };
		chip->Reset();
	}
}
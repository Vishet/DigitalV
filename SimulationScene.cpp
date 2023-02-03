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
		if (SelectPalleteObject(mouseX, mouseY)) break;
		SelectCircuitObject(mouseX, mouseY);
		break;
	}

	case Mouse::Event::Type::LMBReleased:
	{
		DropSelectedObject();
		break;
	}

	case Mouse::Event::Type::RMBPressed:
	{
		ToggleSwitches(mouseX, mouseY);
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

Object* SimulationScene::GetClickedPalleteObject(int mouseX, int mouseY) noexcept
{
	auto palleteLayer{ GetLayerVector(PALLETE) };
	for (const auto& palleteObject : *palleteLayer)
	{
		if (palleteObject->IsColliding(
				static_cast<float>(mouseX), 
				static_cast<float>(mouseY)
			)
		)
			return palleteObject->Clone();
	}

	return nullptr;
}

bool SimulationScene::SelectPalleteObject(int mouseX, int mouseY) noexcept
{
	Object* palleteObject{
		GetClickedPalleteObject(
			mouseX,
			mouseY
		)
	};

	if (palleteObject)
	{
		AddObject(SELECTED_OBJECT, palleteObject);
		return true;
	}
	else
		return false;
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


Object* SimulationScene::GetClickedCircuitObject(float x, float y) noexcept
{
	auto chipsLayer{ GetLayerVector(LayerIndex::CHIPS) };
	auto togglesLayer{ GetLayerVector(LayerIndex::TOGGLES) };

	LayerVector allCircuitLayers{};
	allCircuitLayers.reserve(chipsLayer->size() + togglesLayer->size());
	allCircuitLayers.insert(allCircuitLayers.end(), chipsLayer->begin(), chipsLayer->end());
	allCircuitLayers.insert(allCircuitLayers.end(), togglesLayer->begin(), togglesLayer->end());

	for (auto it{ allCircuitLayers.rbegin() }; it != allCircuitLayers.rend(); ++it)
	{
		auto object{ dynamic_cast<Object*>(*it) };
		if (object->IsColliding(x, y))
			return object;
	}

	return nullptr;
}

void SimulationScene::SelectCircuitObject(int mouseX, int mouseY) noexcept
{
	Object* object{ GetClickedCircuitObject(static_cast<float>(mouseX), static_cast<float>(mouseY)) };
	if (object)
	{
		LayerIndex objectLayerIndex{ object->GetLayerIndex() };
		MoveObjectLayer(
			object->GetLayerIndex(), 
			GetObjectIndex(objectLayerIndex, object), 
			LayerIndex::SELECTED_OBJECT
		);
	}
}

void SimulationScene::ToggleSwitches(int mouseX, int mouseY) noexcept
{
	const LayerVector* togglesLayer{ GetLayerVector(LayerIndex::TOGGLES) };

	for (auto it{ togglesLayer->rbegin() }; it != togglesLayer->rend(); ++it)
	{
		ToggleSwitch* toggleSwitch{ dynamic_cast<ToggleSwitch*>(*it) };
		if (toggleSwitch->IsColliding(static_cast<float>(mouseX), static_cast<float>(mouseY)))
		{
			toggleSwitch->ToggleState();
			break;
		}
	}
}
#include "SimulationScene.h"

#include "Chip.h"
#include "ToggleSwitch.h"

void SimulationScene::Load()
{
	Chip* NANDChip{ new Chip(150.0f, 632.5f, 200.0f, 75.0f, L"NAND") };
	NANDChip->AddInput(-100.0f, 30.0f);
	NANDChip->AddInput(-100.0f, -30.0f);
	AddObject(Layer::PALLETE, NANDChip);

	ToggleSwitch* toggleSwitch{ new ToggleSwitch(400.0f, 632.5f, 50.0f, 1.0f, 0.0f, 0.0f, 0.5f) };
	AddObject(Layer::PALLETE, toggleSwitch);
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

		if(!SelectPalleteObject(mouseX, mouseY));
			SelectCircuitObject(mouseX, mouseY);
	}
	else if (eventType == Mouse::Event::Type::LMBReleased)
	{
		DropSelectedObject();
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
	const LayerVector* selectedObjectLayer{ GetLayerVector(Layer::SELECTED_OBJECT) };
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
	auto selectedObjectLayer{ GetLayerVector(Layer::SELECTED_OBJECT) };
	if (!selectedObjectLayer->empty())
	{
		MoveObjectLayer(Layer::SELECTED_OBJECT, 0, Layer::CIRCUIT);
	}
}


Object* SimulationScene::GetClickedCircuitObject(float x, float y) noexcept
{
	auto circuitLayer{ GetLayerVector(CIRCUIT) };
	for (auto it{ circuitLayer->rbegin() }; it != circuitLayer->rend(); ++it)
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
		MoveObjectLayer(object->GetLayerIndex(), GetObjectIndex(CIRCUIT, object), Layer::SELECTED_OBJECT);
}
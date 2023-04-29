#pragma once

#include "Scene.h"
#include "Chip.h"
#include "Mouse.h"
#include "Wire.h"

class SimulationScene : public Scene
{
private:
	const Mouse* mouse{ Mouse::GetMousePointer() };
	//int maxX;

public:
	SimulationScene() = default;

	SimulationScene(const SimulationScene&) = delete;
	SimulationScene(const SimulationScene&&) = delete;
	SimulationScene operator=(const SimulationScene&) = delete;
	SimulationScene operator=(const SimulationScene&&) = delete;

	void Load() override;
	void KeyInput(const Keyboard::Event& keyEvent) noexcept override;
	void MouseInput(const Mouse::Event& mouseEvent) noexcept override;
	void Update() override;

private:
	Object* GetSelectedObject() const noexcept;

	void SelectPalleteObject(Object* palleteObject) noexcept;
	void DragSelectedObject() noexcept;
	void DropSelectedObject() noexcept;

	void SelectCircuitObject(Object* circuitObject) noexcept;

	void AddWire(ChipOutput* output) noexcept;
	void DropSelectedWire(Wire* selectedWire, ChipInput* chipInput) noexcept;
	void ResetChips() noexcept;
};


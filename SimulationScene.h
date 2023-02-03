#pragma once

#include "Scene.h"
#include "Chip.h"
#include "Mouse.h"

class SimulationScene : public Scene
{
private:
	const Mouse* mouse{ Mouse::GetMousePointer() };

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
	void SelectPalleteObject(Object* palleteObject) noexcept;
	void DragSelectedObject() noexcept;
	void DropSelectedObject() noexcept;

	void SelectCircuitObject(Object* circuitObject) noexcept;

	void ToggleSwitches(int mouseX, int mouseY) noexcept;
	bool SelectWireOutput(int mouseX, int mouseY) noexcept;
};


#pragma once

#include "Scene.h"
#include "Chip.h"
#include "Mouse.h"

class SimulationScene : public Scene
{
private:
	enum Layer {
		CIRCUIT,
		PALLETE,
		GUI,
		SELECTED_OBJECT
	};

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
	bool IsPointInRect(float x, float y, float recX, float recY, float recX2, float rectY2) const noexcept;
	
	Object* GetClickedPalleteObject(int mouseX, int mouseY) noexcept;
	bool SelectPalleteObject(int mouseX, int mouseY) noexcept;
	void DragSelectedObject() noexcept;
	void DropSelectedObject() noexcept;

	
	Object* GetClickedCircuitObject(float x, float y) noexcept;
	void SelectCircuitObject(int mouseX, int mouseY) noexcept;
	void DropSelectedChip() noexcept;
	void DragSelectedChip() noexcept;
	
};


#pragma once

#include "Scene.h"
#include "Chip.h"

class SimulationScene : public Scene
{
private:
	enum Layer {
		CIRCUIT,
		GUI,
		GUI_CHIPS,
		SELECTED_CHIP
	};

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
	Chip* GetClickedGUIChip(float x, float y) noexcept;
};


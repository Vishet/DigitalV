#pragma once

#include "Scene.h"

class SimulationScene : public Scene
{
public:
	SimulationScene() = default;

	SimulationScene(const SimulationScene&) = delete;
	SimulationScene(const SimulationScene&&) = delete;
	SimulationScene operator=(const SimulationScene&) = delete;
	SimulationScene operator=(const SimulationScene&&) = delete;

	void Load() override;
	void Update() override;
};


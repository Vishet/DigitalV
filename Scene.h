#pragma once

#include "Object.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <vector>
#include <array>
#include <bitset>

constexpr size_t maxLayers{ 8u };

using LayerVector = std::vector<Object*>;
using LayersArray = std::array<LayerVector*, maxLayers>;

class Scene
{
private:
	std::array<LayerVector*, maxLayers> layersArray{};

public:
	Scene();

	Scene(const Scene&) = delete;
	Scene(const Scene&&) = delete;
	Scene operator=(const Scene&) = delete;
	Scene operator=(const Scene&&) = delete;

	virtual void Load() = 0;
	virtual void Unload() noexcept;
	virtual void Update() = 0;
	virtual void Render();

	void AddObject(size_t layerIndex, Object* object) noexcept;
};


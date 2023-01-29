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
using Layer = std::size_t;
using ObjectIndex = std::size_t;

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
	virtual void KeyInput(const Keyboard::Event& keyEvent) = 0;
	virtual void MouseInput(const Mouse::Event& mouseEvent) = 0;
	virtual void Update() = 0;
	virtual void Render();

	ObjectIndex AddObject(Layer layerIndex, Object* object) noexcept;
	void DeleteObject(Layer layerIndex, ObjectIndex index) noexcept;
	Object* GetObject(Layer layerIndex, ObjectIndex index) const noexcept;
	ObjectIndex MoveObjectLayer(Layer sourceLayer, ObjectIndex index, Layer destinationLayer);

	const LayerVector* GetLayerVector(Layer layerIndex) const noexcept;
};


#pragma once

#include "Object.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "LayersIndexes.h"
#include "Collision.h"
#include <vector>
#include <array>
#include <bitset>
#include "GUI.h"

constexpr size_t maxLayers{ 8u };

using LayerVector = std::vector<Object*>;
using LayersArray = std::array<LayerVector*, maxLayers>;
using ObjectIndex = std::size_t;

class Scene
{
private:
	std::array<LayerVector*, maxLayers> layersArray{};
	GUI* loadedGUI;
	int maxX{};
	int maxY{};

public:
	Scene();

	Scene(const Scene&) = delete;
	Scene(const Scene&&) = delete;
	Scene operator=(const Scene&) = delete;
	Scene operator=(const Scene&&) = delete;

	virtual void Load() = 0;
	void LoadGUI(GUI* loadedGUI);

	virtual void Unload() noexcept;

	virtual void KeyInput(const Keyboard::Event& keyEvent) = 0;
	virtual void MouseInput(const Mouse::Event& mouseEvent) = 0;
	void OnKeyInput(const Keyboard::Event& keyEvent) noexcept;
	void OnMouseInput(const Mouse::Event& mouseEvent) noexcept;

	virtual void Update() = 0;
	virtual void Render();

	ObjectIndex AddObject(LayerIndex layerIndex, Object* object) noexcept;
	void DeleteObject(LayerIndex layerIndex, ObjectIndex index) noexcept;
	void DeleteObject(Object*) noexcept;
	Object* GetObject(LayerIndex layerIndex, ObjectIndex index) const noexcept;
	ObjectIndex GetObjectIndex(LayerIndex layerIndex, const Object* object) const noexcept;
	ObjectIndex MoveObjectLayer(LayerIndex sourceLayer, ObjectIndex index, LayerIndex destinationLayerIndex);
	ObjectIndex MoveObjectLayer(Object* object, LayerIndex destinationLayerIndex);
	const LayerVector* GetLayerVector(LayerIndex layerIndex) const noexcept;

	Collision GetCollidedObject(int x, int y);
};


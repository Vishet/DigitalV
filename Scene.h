#pragma once

#include "Object.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "LayersIndexes.h"
#include "CollisionType.h"
#include <vector>
#include <array>
#include <bitset>

constexpr size_t maxLayers{ 8u };

using LayerVector = std::vector<Object*>;
using LayersArray = std::array<LayerVector*, maxLayers>;
using ObjectIndex = std::size_t;

class Scene
{
public:
	struct ClickEvent
	{
		CollisionType type;
		int mouseX;
		int mouseY;
		Object* object;
	};

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

	ObjectIndex AddObject(LayerIndex layerIndex, Object* object) noexcept;
	void DeleteObject(LayerIndex layerIndex, ObjectIndex index) noexcept;
	Object* GetObject(LayerIndex layerIndex, ObjectIndex index) const noexcept;
	ObjectIndex GetObjectIndex(LayerIndex layerIndex, const Object* object) const noexcept;
	ObjectIndex MoveObjectLayer(LayerIndex sourceLayer, ObjectIndex index, LayerIndex destinationLayer);
	const LayerVector* GetLayerVector(LayerIndex layerIndex) const noexcept;

	ClickEvent GetCollidedObject(int x, int y);
};


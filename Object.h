#pragma once

#include "LayersIndexes.h"

class Object
{
private:
	float x;
	float y;
	bool isInLayer{ false };
	LayerIndex originalLayerIndex;
	LayerIndex currentLayerIndex{};

public:
	Object(float x, float y, LayerIndex originaLayerIndex);
	Object(const Object& object);
	virtual Object* Clone() { return new Object(*this); }

	Object(const Object&&) = delete;
	Object operator=(const Object&) = delete;
	Object operator=(const Object&&) = delete;

	virtual void Draw() {}
	virtual bool IsColliding(float x, float y) { return false; }

	inline void SetX(float x) noexcept { this->x = x; }
	inline void SetY(float y) noexcept { this->y = y; }
	virtual void SetPosition(float x, float y) noexcept { this->x = x; this->y = y; }

	void SetLayerIndex(LayerIndex layerIndex) noexcept;
	void RemoveLayerIndex() noexcept { this->isInLayer = false; }

	inline float GetX() const noexcept { return x; }
	inline float GetY() const noexcept { return y; }

	inline LayerIndex GetLayerIndex() const noexcept { return this->currentLayerIndex; }
	inline LayerIndex GetOriginalLayerIndex() const noexcept { return this->originalLayerIndex; }
	inline bool IsInLayer() const noexcept { return this->isInLayer; }
};


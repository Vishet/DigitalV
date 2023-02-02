#pragma once

#include <vector> // size_t

using LayerIndex = std::size_t;

class Object
{
private:
	float x;
	float y;
	bool isInLayer{ false };
	LayerIndex currentLayerIndex{ 0 };

public:
	Object(float x, float y);
	Object(const Object& object);

	Object(const Object&&) = delete;
	Object operator=(const Object&) = delete;
	Object operator=(const Object&&) = delete;

	virtual void Draw() = 0;
	virtual bool IsColliding(float x, float y) = 0;

	inline void SetX(float x) noexcept { this->x = x; }
	inline void SetY(float y) noexcept { this->y = y; }
	inline void SetPosition(float x, float y) noexcept { this->x = x; this->y = y; }

	void SetLayerIndex(LayerIndex layerIndex) noexcept;
	void RemoveLayerIndex() noexcept { this->isInLayer = false; }

	inline float GetX() const noexcept { return x; }
	inline float GetY() const noexcept { return y; }

	inline LayerIndex GetLayerIndex() const noexcept { return this->currentLayerIndex; }
	inline bool IsInLayer() const noexcept { return this->isInLayer; }
};


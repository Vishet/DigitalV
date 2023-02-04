#pragma once

#include "Object.h"
#include "CollisionType.h"
#include "Wire.h"

class ChipOutput : public Object
{
private:
	bool state{};
	float xOffset{};
	float yOffset{};
	static constexpr float radius{ 5.0f };
	static constexpr float r{ 0.0f };
	static constexpr float g{ 0.0f };
	static constexpr float b{ 0.5f };
	Wire* connectedWire{};

public:
	ChipOutput(
		float chipX, float chipY,
		float xOffset, float yOffset,
		bool state = false
	);
	ChipOutput(const ChipOutput& chipOutput);
	ChipOutput(const ChipOutput&& ChipOutput);

	ChipOutput operator=(const ChipOutput&) = delete;
	ChipOutput operator=(const ChipOutput&&) = delete;

	float GetXOffset() const noexcept { return xOffset; }
	float GetYOffset() const noexcept { return yOffset; }

	void SetState(bool state) noexcept;
	void Draw() const override;
	void SetPosition(float x, float y) noexcept override;
	Collision IsColliding(float x, float y) override;
	inline void ConnectWire(Wire* wire) noexcept { this->connectedWire = wire; }
	inline Wire* GetConnectedWire() const noexcept { return this->connectedWire; }
};

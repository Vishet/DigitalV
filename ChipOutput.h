#pragma once

#include "Object.h"
#include "CollisionType.h"
#include "Wire.h"

class ChipOutput : public Object
{
private:
	bool state{};
	float xOffset;
	float yOffset;
	float radius;
	float rOn;
	float gOn;
	float bOn;
	float aOn;
	float rOff;
	float gOff;
	float bOff;
	float aOff;
	Wire* connectedWire{};

public:
	ChipOutput(
		float chipX, float chipY,
		float xOffset, float yOffset,
		float radius,
		float rOff, float gOff, float bOff,
		float rOn, float gOn, float bOn,
		float aOff = 1.0f, float aOn = 1.0f
	);
	ChipOutput(const ChipOutput& chipOutput);
	ChipOutput(const ChipOutput&& ChipOutput) noexcept;

	ChipOutput operator=(const ChipOutput&) = delete;
	ChipOutput operator=(const ChipOutput&&) = delete;

	float GetXOffset() const noexcept { return xOffset; }
	float GetYOffset() const noexcept { return yOffset; }
	bool GetState() const noexcept { return state; }

	void SetState(bool state) noexcept;
	void Draw() const override;
	void SetPosition(float x, float y) noexcept override;
	Collision IsColliding(float x, float y) override;
	inline void ConnectWire(Wire* wire) noexcept { this->connectedWire = wire; }
	inline Wire* GetConnectedWire() const noexcept { return this->connectedWire; }
};

#pragma once

#include "Object.h"
#include "Collision.h"
#include "Wire.h"

class Chip;

class ChipInput : public Object
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
	Chip* parentChip;

public:
	ChipInput(
		Chip* parentChip,
		float chipX, float chipY,
		float xOffset, float yOffset,
		float radius,
		float rOff, float gOff, float bOff,
		float rOn, float gOn, float bOn,
		float aOff = 1.0f, float aOn = 1.0f
	);
	ChipInput(const ChipInput& chipInput);
	ChipInput(const ChipInput&& chipInput) noexcept;

	ChipInput operator=(const ChipInput&) = delete;
	ChipInput operator=(const ChipInput&&) = delete;

	float GetXOffset() const noexcept { return xOffset; }
	float GetYOffset() const noexcept { return yOffset; }
	bool GetState() const noexcept { return state; }

	void SetState(bool state) noexcept;
	void Draw() const override;
	void SetPosition(float x, float y) noexcept override;
	Collision IsColliding(float x, float y) override;
	void ConnectWire(Wire* wire) noexcept;
	inline void SetParentChip(Chip* parentChip) noexcept { this->parentChip = parentChip; }
};


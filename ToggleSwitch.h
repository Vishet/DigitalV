#pragma once

#include "Object.h"
#include "ChipOutput.h"

class ToggleSwitch : public Object
{
private:
	bool state{};
	float radius;
	float strokeWidth;
	float r;
	float g;
	float b;
	float a;
	static constexpr float lineWidth{ 25.0f };
	ChipOutput output;

public:
	ToggleSwitch(
		float x, float y, 
		float radius, float strokeWidth, 
		float r, float g, float b, float a = 1.0f
	);
	ToggleSwitch(const ToggleSwitch& toggleSwitch);

	Object* Clone() override { return new ToggleSwitch(*this); }

	ToggleSwitch(const ToggleSwitch&&) = delete;
	ToggleSwitch operator=(const ToggleSwitch&) = delete;
	ToggleSwitch operator=(const ToggleSwitch&&) = delete;

	Collision IsColliding(float x, float y) override;
	void ToggleState() noexcept;
	void Draw() const override;
	void SetPosition(float x, float y) noexcept override;
	ChipOutput* GetOutputPointer() noexcept { return &output; }
};

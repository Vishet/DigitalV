#pragma once

#include "Object.h"

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

public:
	ToggleSwitch(
		float x, float y, 
		float radius, float strokeWidth, 
		float r, float g, float b, float a = 1.0f
	);

	ToggleSwitch(const ToggleSwitch&) = delete;
	ToggleSwitch(const ToggleSwitch&&) = delete;
	ToggleSwitch operator=(const ToggleSwitch&) = delete;
	ToggleSwitch operator=(const ToggleSwitch&&) = delete;

	bool IsColliding(float x, float y) const noexcept;
	void ToggleState() noexcept;
	void Draw() override;
};

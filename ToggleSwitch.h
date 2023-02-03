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
	ToggleSwitch(const ToggleSwitch& toggleSwitch);

	Object* Clone() override { return new ToggleSwitch(GetX(), GetY(), radius, strokeWidth, r, g, b, a); }

	ToggleSwitch(const ToggleSwitch&&) = delete;
	ToggleSwitch operator=(const ToggleSwitch&) = delete;
	ToggleSwitch operator=(const ToggleSwitch&&) = delete;

	CollisionType IsColliding(float x, float y) override;
	void ToggleState() noexcept;
	void Draw() override;
};

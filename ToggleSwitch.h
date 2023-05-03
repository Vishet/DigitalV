#pragma once

#include "Object.h"
#include "ChipOutput.h"

class ToggleSwitch : public Object
{
private:
	bool state{};
	float radius{ 25.0f };
	float strokeWidth{ 5.0f };
	float r{ 0.0f };
	float g{ 0.0f };
	float b{ 0.5f };
	float a{ 1.0f };

	float outputR{ 0.5f };
	float outputG{ 0.5f };
	float outputB{ 0.5f };

	float activeOutputR{ 0.0f };
	float activeOutputG{ 0.0f };
	float activeOutputB{ 0.5f };

	float outputRadius{ 5.0f };

	float lineWidth{ 25.0f };
	ChipOutput output;

public:
	ToggleSwitch(float x, float y);
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

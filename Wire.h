#pragma once

#include "Object.h"

class ChipInput;
class ChipOutput;

class Wire : public Object
{
private:
	ChipInput* input{};
	ChipOutput* output;
	bool state;
	float strokeWidth;
	float rOff;
	float gOff;
	float bOff;
	float aOff;
	float rOn;
	float gOn;
	float bOn;
	float aOn;

public:
	Wire(
		ChipOutput* output,
		float strokeWidth, bool state,
		float rOff, float gOff, float bOff,
		float rOn, float gOn, float bOn,
		float aOff = 1.0f, float aOn = 1.0f
	);
	~Wire();

	Wire(const Wire&) = delete;
	Wire(const Wire&&) = delete;
	Wire operator=(const Wire&) = delete;
	Wire operator=(const Wire&&) = delete;

	void Draw() const override;
	void SetInput(ChipInput* input);
	void UpdateState() noexcept;
	inline bool GetState() const noexcept { return state; }
};
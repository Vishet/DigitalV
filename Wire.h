#pragma once

#include "Object.h"

class ChipInput;
class ChipOutput;

class Wire : public Object
{
private:
	ChipInput* input{};
	ChipOutput* output;
	static constexpr float strokeWidth{ 2.0f };
	static constexpr float r{ 0.0f };
	static constexpr float g{ 0.0f };
	static constexpr float b{ 0.5f };
	static constexpr float a{ 1.0f };

public:
	Wire(ChipOutput* output);

	Wire(const Wire&) = delete;
	Wire(const Wire&&) = delete;
	Wire operator=(const Wire&) = delete;
	Wire operator=(const Wire&&) = delete;

	void Draw() const override;
	void SetInput(ChipInput* input);
};
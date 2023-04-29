#pragma once

#include "Chip.h"

class NANDChip : public Chip
{
private:
	ChipInput* inputA{};
	ChipInput* inputB{};
	ChipOutput* output{};
	static constexpr float width{ 200.0f };
	static constexpr float height{ 75.0f };

public:
	NANDChip(float x, float y, const std::wstring& label);
	NANDChip(const NANDChip&);
	Object* Clone() override;
	~NANDChip();

	NANDChip(const NANDChip&&) = delete;
	NANDChip operator=(const NANDChip&) = delete;
	NANDChip operator=(const NANDChip&&) = delete;

	void UpdateOutput() noexcept override;
};
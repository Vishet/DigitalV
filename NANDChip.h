#pragma once
#include "Chip.h"
class NANDChip : public Chip
{
private:
	static constexpr float width{ 200.0f };
	static constexpr float height{ 75.0f };

public:
	NANDChip(float x, float y);

	NANDChip(const NANDChip&) = delete;
	NANDChip(const NANDChip&&) = delete;
	NANDChip operator=(const NANDChip&) = delete;
	NANDChip operator=(const NANDChip&&) = delete;

	void Draw() override;
	bool IsColliding(float x, float y) override;
};


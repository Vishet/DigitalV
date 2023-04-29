#pragma once
#include "GUIItem.h"
#include <string>

class NANDChipItem : public GUIItem
{
private:
	static constexpr int width{ 200 };
	static constexpr int height{ 75 };
	static constexpr std::wstring_view label{ L"NAND" };
	static constexpr int ioRadius{ 5 };

	static constexpr float r{ 1.0f };
	static constexpr float g{ 1.0f };
	static constexpr float b{ 1.0f };
	static constexpr float ioR{ 0.5f };
	static constexpr float ioG{ 0.5f };
	static constexpr float ioB{ 0.5f };
	static constexpr float textR{ 0.0f };
	static constexpr float textG{ 0.0f };
	static constexpr float textB{ 1.0f };

	static constexpr int inputXOffset{ -100 };
	static constexpr int inputYOffset{ 30 };
	static constexpr int outputXOffset{ 100 };
	static constexpr int outputYOffset{ 0 };

public:
	NANDChipItem(int x, int y, int maxX, int maxY);

	NANDChipItem(const NANDChipItem& object) = delete;
	NANDChipItem(const NANDChipItem&& object) = delete;
	NANDChipItem operator=(const NANDChipItem&) = delete;
	NANDChipItem operator=(const NANDChipItem&&) = delete;

	void Draw() override;
};


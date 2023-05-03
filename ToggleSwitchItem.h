#pragma once

#include "PickupItem.h"

class ToggleSwitchItem : public PickupItem
{
private:
	static constexpr float radius{ 25.0f };
	static constexpr float strokeWidth{ 5.0f };
	static constexpr float r{ 0.0f };
	static constexpr float g{ 0.0f };
	static constexpr float b{ 0.5f };
	static constexpr float a{ 1.0f };
	static constexpr float lineWidth{ 25.0f };

	static constexpr float outputR{ 0.5f };
	static constexpr float outputG{ 0.5f };
	static constexpr float outputB{ 0.5f };
	static constexpr float outputRadius{ 5.0f };

public:
	ToggleSwitchItem(int x, int y);

	void Draw() override;

	//void KeyInput(const Keyboard::Event& keyEvent) noexcept override;
	void MouseInput(const Mouse::Event& mouseEvent) noexcept override;

private:
	bool IsColliding(int x, int y) const noexcept;
	void DrawSwitch(int x, int y);
};


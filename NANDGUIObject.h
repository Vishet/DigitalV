#pragma once

#include "GUIChip.h"

class NANDGUIObject : public GUIChip
{
private:
	float x;
	float y;
	static constexpr float width{ 200.0f };
	static constexpr float height{ 75.0f };

public:
	NANDGUIObject(float x, float y);

	NANDGUIObject(const NANDGUIObject&) = delete;
	NANDGUIObject(const NANDGUIObject&&) = delete;
	NANDGUIObject operator=(const NANDGUIObject&) = delete;
	NANDGUIObject operator=(const NANDGUIObject&&) = delete;

	void Draw() override;
	bool IsColliding(float x, float y) noexcept override;
	Chip* GetChip() noexcept override;
};
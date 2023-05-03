#pragma once

#include "Mouse.h"
#include "Keyboard.h"

class GUIItem
{
private:
	int x, y;

public:
	GUIItem(int x, int y);

	GUIItem(const GUIItem& object) = delete;
	GUIItem(const GUIItem&& object) = delete;
	GUIItem operator=(const GUIItem&) = delete;
	GUIItem operator=(const GUIItem&&) = delete;

	virtual void Draw() = 0;

	inline void SetX() { this->x = x; }
	inline void SetY() { this->y = y; }

	int GetX() const noexcept;
	int GetY() const noexcept;

	virtual void KeyInput(const Keyboard::Event& keyEvent) noexcept;
	virtual void MouseInput(const Mouse::Event& mouseEvent) noexcept;
};


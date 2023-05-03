#pragma once

#include "GUIItem.h"
#include <vector>

class GUI
{
private:
	std::vector<GUIItem*> itemsVector{};

public:
	GUI();

	void AddItem(GUIItem* guiItem) noexcept;
	void Render() noexcept;

	virtual void OnClick(){};
	virtual void Load() = 0;
	virtual void Unload();

	void OnKeyInput(const Keyboard::Event& keyEvent) noexcept;
	void OnMouseInput(const Mouse::Event& mouseEvent) noexcept;
};


#pragma once

#include "GUIItem.h"
#include <vector>

class GUI
{
private:
	std::vector<GUIItem*> itemsVector{};
	int maxX, maxY;

public:
	GUI();

	void AddItem(GUIItem* guiItem) noexcept;
	void Render() noexcept;

	virtual void OnClick(){};
	virtual void Load() = 0;
	virtual void Unload();
};


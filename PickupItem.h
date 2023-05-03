#pragma once

#include "GUIItem.h"

class PickupItem : public GUIItem
{
private:
	int pickupX{};
	int pickupY{};
	bool isSelected{ false };

public:
	PickupItem(int x, int y);

	void PickItem(int x, int y);
	void UpdatePickup(int x, int y);
	void DropPickup();

	inline int GetPickupX() const noexcept { return pickupX; }
	inline int GetPickupY() const noexcept { return pickupY; }
	inline bool IsSelected() const noexcept { return isSelected; }
};


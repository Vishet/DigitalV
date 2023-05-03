#include "PickupItem.h"

PickupItem::PickupItem(int x, int y) :
	GUIItem(x, y)
{
}

void PickupItem::PickItem(int x, int y)
{
	pickupX = x;
	pickupY = y;
	isSelected = true;
}

void PickupItem::UpdatePickup(int x, int y)
{
	if (isSelected)
	{
		pickupX = x;
		pickupY = y;
	}
}

void PickupItem::DropPickup()
{
	isSelected = false;
}

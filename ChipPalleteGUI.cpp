#include "ChipPalleteGUI.h"

#include "NANDChipItem.h"
#include "ToggleSwitchItem.h"

ChipPalleteGUI::ChipPalleteGUI() :
	GUI()
{
}

void ChipPalleteGUI::Load()
{
	AddItem(new NANDChipItem(150, 633));
	AddItem(new ToggleSwitchItem(400, 633));
}

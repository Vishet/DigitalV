#include "ChipPalleteGUI.h"

#include "NANDChipItem.h"

ChipPalleteGUI::ChipPalleteGUI() :
	GUI()
{
}

void ChipPalleteGUI::Load()
{
	AddItem(new NANDChipItem())
}

#include "GUI.h"

GUI::GUI() :
	maxX
{

}

void GUI::AddItem(GUIItem* guiItem) noexcept
{
	itemsVector.push_back(guiItem);
}

void GUI::Render() noexcept
{
	for (const auto item : itemsVector)
	{
		item->Draw();
	}
}

void GUI::Unload()
{
	for (auto item : itemsVector)
	{
		delete item;
	}
}


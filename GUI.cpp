#include "GUI.h"

GUI::GUI()
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

void GUI::OnKeyInput(const Keyboard::Event& keyEvent) noexcept
{
	for (auto item : itemsVector)
	{
		item->KeyInput(keyEvent);
	}
}

void GUI::OnMouseInput(const Mouse::Event& mouseEvent) noexcept
{
	for (auto item : itemsVector)
	{
		item->MouseInput(mouseEvent);
	}
}


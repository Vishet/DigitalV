#include "NANDChipItem.h"

#include "Graphics.h"
#include "SceneManager.h"
#include "NANDChip.h"

NANDChipItem::NANDChipItem(int x, int y) :
	PickupItem(x, y)
{
}

void NANDChipItem::Draw()
{
	DrawChip(GetX(), GetY());

	if (IsSelected())
	{
		DrawChip(GetPickupX(), GetPickupY());
	}
}



void NANDChipItem::KeyInput(const Keyboard::Event& keyEvent) noexcept
{
}

void NANDChipItem::MouseInput(const Mouse::Event& mouseEvent) noexcept
{
	int mouseX = mouseEvent.GetX();
	int mouseY = mouseEvent.GetY();

	switch (mouseEvent.GetType())
	{

	case Mouse::Event::Type::LMBPressed:
	{
		if (IsColliding(mouseX, mouseY))
		{
			PickItem(mouseX, mouseY);
		}
		break;
	}

	case Mouse::Event::Type::Move:
	{
		if (IsSelected())
		{
			UpdatePickup(mouseX, mouseY);
		}
		break;
	}

	case Mouse::Event::Type::LMBReleased:
	{
		if (IsSelected())
		{
			DropPickup();
			Scene* currentScene{ SceneManager::GetCurrentScene() };
			currentScene->AddObject(
				CHIPS, 
				new NANDChip(static_cast<float>(mouseX), static_cast<float>(mouseY), L"NAND")
			);
		}
		break;
	}

	}
}

bool NANDChipItem::IsColliding(int x, int y) const noexcept
{
	int left{ GetX() - width / 2 };
	int right{ GetX() + width / 2 };
	int top{ GetY() - height / 2 };
	int bottom{ GetY() + height / 2 };

	return (
		x >= left && 
		x < right && 
		y >= top && 
		y < bottom
	);
}

void NANDChipItem::DrawChip(int x, int y)
{
	auto graphics{ Graphics::GetGraphicsPointer() };

	graphics->FillRectangle(
		static_cast<float>(x - width / 2), static_cast<float>(y - height / 2),
		static_cast<float>(x + width / 2), static_cast<float>(y + height / 2),
		r, g, b
	);

	graphics->DrawCenteredText(
		label.data(),
		static_cast<float>(x - width / 2), static_cast<float>(y - height / 2),
		static_cast<float>(x + width / 2), static_cast<float>(y + height / 2),
		textR, textG, textB
		);

	graphics->FillCircle(
		static_cast<float>(x + inputXOffset), static_cast<float>(y - inputYOffset),
		static_cast<float>(ioRadius),
		ioR, ioG, ioB
	);

	graphics->FillCircle(
		static_cast<float>(x + inputXOffset), static_cast<float>(y + inputYOffset),
		static_cast<float>(ioRadius),
		ioR, ioG, ioB
	);

	graphics->FillCircle(
		static_cast<float>(x + outputXOffset), static_cast<float>(y + outputYOffset),
		static_cast<float>(ioRadius),
		ioR, ioG, ioB
	);
}
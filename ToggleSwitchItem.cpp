#include "ToggleSwitchItem.h"
#include "Graphics.h"
#include "SceneManager.h"
#include "ToggleSwitch.h"

ToggleSwitchItem::ToggleSwitchItem(int x, int y) :
	PickupItem(x, y)
{
}

void ToggleSwitchItem::Draw()
{
	DrawSwitch(GetX(), GetY());

	if (IsSelected())
	{
		DrawSwitch(GetPickupX(), GetPickupY());
	}
}

void ToggleSwitchItem::MouseInput(const Mouse::Event& mouseEvent) noexcept
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
				TOGGLES,
				new ToggleSwitch(static_cast<float>(mouseX), static_cast<float>(mouseY))
			);
		}
		break;
	}

	}
}

bool ToggleSwitchItem::IsColliding(int x, int y) const noexcept
{
	return (sqrt(pow(x - GetX(), 2) + pow(y - GetY(), 2)) <= radius);
}

void ToggleSwitchItem::DrawSwitch(int x, int y)
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };

	graphics->DrawCircle(
		static_cast<float>(x), 
		static_cast<float>(y), 
		radius, strokeWidth, r, g, b, a
	);

	graphics->DrawLine(
		static_cast<float>(x + radius), static_cast<float>(y),
		static_cast<float>(x + radius + lineWidth), static_cast<float>(y),
		strokeWidth,
		r, g, b, a
	);

	graphics->FillCircle(
		static_cast<float>(x + radius + lineWidth),
		static_cast<float>(y),
		outputRadius, outputR, outputG, outputB
	);
}

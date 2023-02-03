#include "ToggleSwitch.h"
#include "Graphics.h"
#include "LayersIndexes.h"

ToggleSwitch::ToggleSwitch(
	float x, float y,
	float radius, float strokeWidth,
	float r, float g, float b, float a) :
	Object(x, y, LayerIndex::TOGGLES),
	radius{ radius }, strokeWidth{ strokeWidth },
	r{ r }, g{ g }, b{ b }, a{ a }
{
}
ToggleSwitch::ToggleSwitch(const ToggleSwitch& toggleSwitch) :
	Object(toggleSwitch)
{
	state = toggleSwitch.state;
	radius = toggleSwitch.radius;
	strokeWidth = toggleSwitch.strokeWidth;
	r = toggleSwitch.r;
	g = toggleSwitch.g;
	b = toggleSwitch.b;
	a = toggleSwitch.a;
}

CollisionType ToggleSwitch::IsColliding(float x, float y)
{
	float distance = static_cast<float>(sqrt(pow(GetX() - x, 2) + pow(GetY() - y, 2)));
	if (distance <= radius)
	{
		if (GetLayerIndex() == LayerIndex::TOGGLES)
			return CollisionType::TOGGLE;
		else if (GetLayerIndex() == LayerIndex::PALLETE)
			return CollisionType::PALLETE;
		else
			return CollisionType::NO_COLLISION;
	}
	else
		return CollisionType::NO_COLLISION;
}

void ToggleSwitch::ToggleState() noexcept
{
	state = !state;
}

void ToggleSwitch::Draw()
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };

	if (state)
		graphics->FillCircle(GetX(), GetY(), radius, r, g, b);
	else
		graphics->DrawCircle(GetX(), GetY(), radius, strokeWidth, r, g, b, a);
}
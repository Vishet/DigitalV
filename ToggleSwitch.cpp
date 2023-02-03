#include "ToggleSwitch.h"
#include "Graphics.h"

ToggleSwitch::ToggleSwitch(
	float x, float y, 
	float radius, float strokeWidth,
	float r, float g, float b, float a) :
	Object(x, y),
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

bool ToggleSwitch::IsColliding(float x, float y)
{
	float distance = static_cast<float>(sqrt(pow(GetX() - x, 2) + pow(GetY() - y, 2)));
	return (distance <= radius);
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
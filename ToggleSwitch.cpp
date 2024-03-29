#include "ToggleSwitch.h"
#include "Graphics.h"
#include "LayersIndexes.h"

ToggleSwitch::ToggleSwitch(
	float x, float y,
	float radius, float strokeWidth,
	float r, float g, float b, float a
) :
	Object(x, y, LayerIndex::TOGGLES),
	radius{ radius }, strokeWidth{ strokeWidth },
	r{ r }, g{ g }, b{ b }, a{ a },
	output{ x, y, radius + lineWidth, 0.0f }
{
}

ToggleSwitch::ToggleSwitch(const ToggleSwitch& toggleSwitch) :
	Object(toggleSwitch),
	state{ toggleSwitch.state },
	radius{ toggleSwitch.radius },
	strokeWidth{ toggleSwitch.strokeWidth },
	r{ toggleSwitch.r },
	g{ toggleSwitch.g },
	b{ toggleSwitch.b },
	a{ toggleSwitch.a },
	output{ toggleSwitch.output }
{
}

Collision ToggleSwitch::IsColliding(float x, float y)
{
	Collision collision{ output.IsColliding(x, y) };

	if (collision.type != CollisionType::NO_COLLISION)
		return collision;
	else
	{
		collision.x = x;
		collision.y = y;
		collision.trigger = this;

		float distance = static_cast<float>(sqrt(pow(GetX() - x, 2) + pow(GetY() - y, 2)));
		if (distance <= radius)
		{
			if (GetLayerIndex() == LayerIndex::TOGGLES)
				collision.type = CollisionType::TOGGLE;
			else if (GetLayerIndex() == LayerIndex::PALLETE)
				collision.type = CollisionType::PALLETE;
		}

		return collision;
	}
}

void ToggleSwitch::ToggleState() noexcept
{
	state = !state;
}

void ToggleSwitch::Draw() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };

	if (state)
		graphics->FillCircle(GetX(), GetY(), radius, r, g, b);
	else
		graphics->DrawCircle(GetX(), GetY(), radius, strokeWidth, r, g, b, a);

	graphics->DrawLine(
		GetX() + radius, GetY(),
		GetX() + radius + lineWidth, GetY(),
		strokeWidth,
		r, g, b, a
	);

	output.Draw();
}

void ToggleSwitch::SetPosition(float x, float y) noexcept
{
	Object::SetPosition(x, y);
	output.SetPosition(x, y);
}
#pragma once

#include "CollisionType.h"

class Object;

struct Collision
{
	float x{};
	float y{};
	CollisionType type{};
	Object* trigger{};

	Collision()
	{
	}

	Collision(float x, float y, CollisionType type, Object* trigger) :
		x{ x },
		y{ y },
		type{ type },
		trigger{ trigger }
	{
	}
};
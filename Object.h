#pragma once

class Object
{
public:
	enum class Type
	{
		NANDGUIObject
	};

public:
	Object() = default;

	Object(const Object&) = delete;
	Object(const Object&&) = delete;
	Object operator=(const Object&) = delete;
	Object operator=(const Object&&) = delete;

	virtual void Draw() = 0;
	virtual bool IsColliding(float x, float y) = 0;
};


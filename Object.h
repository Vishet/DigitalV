#pragma once

class Object
{
public:
	Object() = default;

	Object(const Object&) = delete;
	Object(const Object&&) = delete;
	Object operator=(const Object&) = delete;
	Object operator=(const Object&&) = delete;

	virtual void Draw() {};
};


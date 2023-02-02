#pragma once

class Object
{
private:
	float x;
	float y;

public:
	enum class Type
	{
		NANDGUIObject
	};

public:
	Object(float x, float y);
	Object(const Object&) = default;
	
	Object(const Object&&) = delete;
	Object operator=(const Object&) = delete;
	Object operator=(const Object&&) = delete;

	virtual void Draw() = 0;
	virtual bool IsColliding(float x, float y) = 0;

	inline void SetX(float x) noexcept { this->x = x; }
	inline void SetY(float y) noexcept { this->y = y; }
	inline void SetPosition(float x, float y) noexcept { this->x = x; this->y = y; }

	inline float GetX() const noexcept { return x; }
	inline float GetY() const noexcept { return y; }
};


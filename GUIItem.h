#pragma once
class GUIItem
{
private:
	int x, y;
	int maxX, maxY;

public:
	GUIItem(int x, int y, int maxX, int maxY);

	GUIItem(const GUIItem& object) = delete;
	GUIItem(const GUIItem&& object) = delete;
	GUIItem operator=(const GUIItem&) = delete;
	GUIItem operator=(const GUIItem&&) = delete;

	virtual void Draw() = 0;

	inline void SetX() { this->x = x; }
	inline void SetY() { this->y = y; }

	int GetX() noexcept;
	int GetY() noexcept;
};


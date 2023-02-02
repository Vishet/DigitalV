#pragma once

#include "Object.h"
#include <vector>
#include <string>

class Chip : public Object
{
private:
	float width{ 200.0f };
	float height{ 75.0f };
	std::wstring label;

public:
	Chip(float x, float y, const std::wstring& label);
	Chip(const Chip&) = default;

	Chip(const Chip&&) = delete;
	Chip operator=(const Chip&) = delete;
	Chip operator=(const Chip&&) = delete;

	void Draw() override;
	bool IsColliding(float x, float y) override;
};


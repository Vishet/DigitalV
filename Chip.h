#pragma once

#include "Object.h"
#include "ChipInput.h"
#include "ChipOutput.h"
#include "CollisionType.h"
#include <vector>
#include <string>

using InputIndex = std::size_t;

class Chip : public Object
{
private:
	float width;
	float height;
	std::wstring label;
	std::vector<ChipInput> inputs{};
	std::vector<ChipOutput> outputs{};

public:
	Chip(float x, float y, float width, float height, const std::wstring& label);
	Chip(const Chip&);
	Object* Clone() override { return new Chip(*this); }
	~Chip();

	Chip(const Chip&&) = delete;
	Chip operator=(const Chip&) = delete;
	Chip operator=(const Chip&&) = delete;

	void Draw() const override;
	Collision IsColliding(float x, float y) override;
	void AddInput(float xOffset, float yOffset) noexcept;
	void AddOutput(float xOffset, float yOffset) noexcept;
	void SetPosition(float x, float y) noexcept override;
};


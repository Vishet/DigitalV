#pragma once

#include "Object.h"
#include <vector>

class Chip : public Object
{
public:
	Chip(float x, float y);

	Chip(const Chip&) = delete;
	Chip(const Chip&&) = delete;
	Chip operator=(const Chip&) = delete;
	Chip operator=(const Chip&&) = delete;
};


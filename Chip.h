#pragma once

#include "Object.h"
#include <vector>

class Chip : public Object
{
public:
	Chip() = default;

	Chip(const Chip&) = delete;
	Chip(const Chip&&) = delete;
	Chip operator=(const Chip&) = delete;
	Chip operator=(const Chip&&) = delete;
};


#pragma once

#include "Object.h"
#include "Chip.h"

class GUIChip : public Object
{
public:
	GUIChip() = default;

	GUIChip(const GUIChip&) = delete;
	GUIChip(const GUIChip&&) = delete;
	GUIChip operator=(const GUIChip&) = delete;
	GUIChip operator=(const GUIChip&&) = delete;

	virtual Chip* GetChip() noexcept = 0;
};


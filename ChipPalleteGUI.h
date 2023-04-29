#pragma once

#include "GUI.h"

class ChipPalleteGUI : public GUI
{
private:


public:
	ChipPalleteGUI();

	ChipPalleteGUI(const ChipPalleteGUI& object) = delete;
	ChipPalleteGUI(const ChipPalleteGUI&& object) = delete;
	ChipPalleteGUI operator=(const ChipPalleteGUI&) = delete;
	ChipPalleteGUI operator=(const ChipPalleteGUI&&) = delete;
	
	void Load() override;
};


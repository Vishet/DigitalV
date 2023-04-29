#include "NANDChip.h"

NANDChip::NANDChip(float x, float y, const std::wstring& label) :
	Chip(x, y, width, height, label)
{
	Chip::AddInput(
		-100.0f, -30.0f, 5.0f,
		0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.5f
	);
	Chip::AddInput(
		-100.0f, 30.0f, 5.0f,
		0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.5f
	);
	Chip::AddOutput(
		100.0f, 0.0f, 5.0f,
		0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.5f
	);

	this->inputA = &inputs.at(0);
	this->inputB = &inputs.at(1);
	this->output = &outputs.at(0);

	this->UpdateOutput();
	this->Reset();
}

NANDChip::NANDChip(const NANDChip& nandChip) :
	Chip(nandChip),
	inputA{ &this->inputs.at(0) },
	inputB{ &this->inputs.at(1) },
	output{ &this->outputs.at(0) }
{
}

Object* NANDChip::Clone()
{
	auto nandChipClone{ new NANDChip(*this) };
	nandChipClone->UpdateOutput();
	return nandChipClone;
}

NANDChip::~NANDChip()
{
}

void NANDChip::UpdateOutput() noexcept
{
	if (!alreadyProcessed)
	{
		bool inputAState{ inputA->GetState() };
		bool inputBState{ inputB->GetState() };
		bool updatedOutputState{ !(inputAState && inputBState) };
		
		alreadyProcessed = true;
		output->SetState(updatedOutputState);
	}
}
#include "Wire.h"
#include "LayersIndexes.h"
#include "Graphics.h"
#include "ChipInput.h"
#include "ChipOutput.h"

Wire::Wire(ChipOutput* output) :
	Object(output->GetX(), output->GetY(), LayerIndex::WIRES),
	output{ output }
{
	output->ConnectWire(this);
}

void Wire::Draw() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };

	graphics->DrawLine(
		output->GetX(), output->GetY(),
		GetX(), GetY(),
		strokeWidth,
		r, g, b, a
	);
}

void Wire::SetInput(ChipInput* input)
{
	this->input = input;
	this->SetPosition(input->GetX(), input->GetY());
	input->ConnectWire(this);
}
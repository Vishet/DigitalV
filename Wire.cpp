#include "Wire.h"
#include "LayersIndexes.h"
#include "Graphics.h"

Wire::Wire(ChipInput* input, ChipOutput* output) :
	Object(input->GetX(), input->GetY(), LayerIndex::WIRES),
	input{ input },
	output{ output }
{
}

void Wire::Draw()
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };

	graphics->DrawLine(
		input->GetX(), input->GetY(),
		output->GetX(), output->GetY(),
		strokeWidth,
		r, g, b, a
	);
}
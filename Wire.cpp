#include "Wire.h"
#include "LayersIndexes.h"
#include "Graphics.h"
#include "ChipInput.h"
#include "ChipOutput.h"

Wire::Wire(
	ChipOutput* output,
	float strokeWidth, bool state,
	float rOff, float gOff, float bOff,
	float rOn, float gOn, float bOn,
	float aOff, float aOn
) :
	Object(output->GetX(), output->GetY(), LayerIndex::WIRES),
	output{ output },
	strokeWidth{ strokeWidth }, state{ state },
	rOff{ rOff }, gOff{ gOff }, bOff{ bOff }, aOff{ aOff },
	rOn{ rOn }, gOn{ gOn }, bOn{ bOn }, aOn{ aOn }
{
	output->ConnectWire(this);
}

Wire::~Wire()
{
	this->output->ConnectWire(nullptr);
	if (this->input)
		this->input->ConnectWire(nullptr);
}

void Wire::Draw() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };

	if(state)
		graphics->DrawLine(
			output->GetX(), output->GetY(),
			GetX(), GetY(),
			strokeWidth,
			rOn, gOn, bOn, aOn
		);
	else
		graphics->DrawLine(
			output->GetX(), output->GetY(),
			GetX(), GetY(),
			strokeWidth,
			rOff, gOff, bOff, aOff
		);
}

void Wire::SetInput(ChipInput* input)
{
	if (input)
	{
		this->SetPosition(input->GetX(), input->GetY());
		input->ConnectWire(this);
	}
	else
		this->input->ConnectWire(nullptr);

	this->input = input;
}

void Wire::UpdateState() noexcept
{
	this->state = output->GetState();
	if(input)
		input->SetState(this->state);
}

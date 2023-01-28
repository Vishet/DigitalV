#include "CrateObject.h"
#include "Graphics.h"

void CrateObject::Draw()
{
	Graphics::GetGraphicsPointer()->FillRectangle(
		100, 100, 400, 400,
		0.0f, 0.5f, 0.5f
	);
}

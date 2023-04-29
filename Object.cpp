#include "Object.h"

Object::Object(float x, float y, LayerIndex originalLayerIndex) :
	x{ x },
	y{ y },
	originalLayerIndex{ originalLayerIndex }
{
}

Object::Object(const Object& object) :
	x{ object.x },
	y{ object.y },
	isInLayer{ object.isInLayer },
	currentLayerIndex{ object.currentLayerIndex },
	originalLayerIndex{ object.originalLayerIndex }
{
}

Object::Object(const Object&& object) noexcept :
	x{ object.x },
	y{ object.y },
	isInLayer{ object.isInLayer },
	currentLayerIndex{ object.currentLayerIndex },
	originalLayerIndex{ object.originalLayerIndex }
{
}

void Object::SetLayerIndex(LayerIndex layerIndex) noexcept
{
	this->currentLayerIndex = layerIndex;
	isInLayer = true;
}

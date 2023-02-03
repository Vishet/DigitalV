#include "Object.h"

Object::Object(float x, float y, LayerIndex originalLayerIndex) :
	x{ x },
	y{ y },
	originalLayerIndex{ originalLayerIndex }
{
}

Object::Object(const Object& object)
{
	this->x = object.x;
	this->y = object.y;
	this->isInLayer = object.isInLayer;
	this->currentLayerIndex = object.currentLayerIndex;
	this->originalLayerIndex = object.originalLayerIndex;
}

void Object::SetLayerIndex(LayerIndex layerIndex) noexcept
{
	this->currentLayerIndex = layerIndex;
	isInLayer = true;
}

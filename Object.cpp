#include "Object.h"

Object::Object(float x, float y) :
	x{ x },
	y{ y }
{
}

Object::Object(const Object& object)
{
	this->x = object.x;
	this->y = object.y;
	this->isInLayer = false;
	this->currentLayerIndex = 0;
}

void Object::SetLayerIndex(LayerIndex layerIndex) noexcept
{
	this->currentLayerIndex = layerIndex;
	isInLayer = true;
}

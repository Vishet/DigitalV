#include "Scene.h"

Scene::Scene()
{
	for (size_t index{ 0 }; index < layersArray.size(); index++)
	{
		layersArray[index] = new LayerVector();
	}
}

void Scene::Unload() noexcept
{
	for (auto& layer : layersArray)
	{
		for (auto& object : *layer)
		{
			delete object;
		}
	}
}

void Scene::Render()
{
	for (auto& layer : layersArray)
	{
		for (auto& object : *layer)
		{
			object->Draw();
		}
	}
}

ObjectIndex Scene::AddObject(Layer layerIndex, Object* object) noexcept
{
	layersArray[layerIndex]->push_back(object);
	return layersArray[layerIndex]->size() - 1;
}

void Scene::DeleteObject(Layer layerIndex, ObjectIndex index) noexcept
{
	auto layer{ layersArray[layerIndex] };
	layer->erase(layer->begin() + index);
}

Object* Scene::GetObject(Layer layerIndex, ObjectIndex index) const noexcept
{
	Object* object{ layersArray[layerIndex]->at(index) };
	return object;
}

ObjectIndex Scene::MoveObjectLayer(Layer srcLayerIndex, ObjectIndex objIndex, Layer destLayerIndex)
{
	Object* object{ GetObject(srcLayerIndex, objIndex) };
	DeleteObject(srcLayerIndex, objIndex);
	return AddObject(destLayerIndex, object);
}

const LayerVector* Scene::GetLayerVector(Layer layerIndex) const noexcept
{
	return layersArray[layerIndex];
}

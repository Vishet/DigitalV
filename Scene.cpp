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
	object->SetLayerIndex(layerIndex);
	return layersArray[layerIndex]->size() - 1;
}

void Scene::DeleteObject(Layer layerIndex, ObjectIndex index) noexcept
{
	auto layer{ layersArray[layerIndex] };
	layer->at(index)->RemoveLayerIndex();
	layer->erase(layer->begin() + index);
}

Object* Scene::GetObject(Layer layerIndex, ObjectIndex index) const noexcept
{
	Object* object{ layersArray[layerIndex]->at(index) };
	return object;
}

ObjectIndex Scene::GetObjectIndex(Layer layerIndex, const Object* object) const noexcept
{
	auto layer{ GetLayerVector(layerIndex) };
	for(auto it{ layer->begin() }; it != layer->end(); it++)
	{
		const Object* objectInLayer{ *it };
		if (objectInLayer == object)
		{
			const ObjectIndex objectIndex{ static_cast<ObjectIndex>(it - layer->begin()) };
			return objectIndex;
		}
	}

	return 0;
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

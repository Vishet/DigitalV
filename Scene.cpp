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
	if (loadedGUI) {
		loadedGUI->Unload();
		delete loadedGUI;
	}

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

ObjectIndex Scene::AddObject(LayerIndex layerIndex, Object* object) noexcept
{
	layersArray[layerIndex]->push_back(object);
	object->SetLayerIndex(layerIndex);
	return layersArray[layerIndex]->size() - 1;
}

void Scene::DeleteObject(LayerIndex layerIndex, ObjectIndex index) noexcept
{
	auto layer{ layersArray[layerIndex] };
	layer->at(index)->RemoveLayerIndex();
	layer->erase(layer->begin() + index);
}

void Scene::DeleteObject(Object* object) noexcept
{
	auto layerIndex{ object->GetLayerIndex() };
	DeleteObject(layerIndex, GetObjectIndex(layerIndex, object));
}

Object* Scene::GetObject(LayerIndex layerIndex, ObjectIndex index) const noexcept
{
	auto layer{ GetLayerVector(layerIndex) };
	if (!layer->empty())
	{
		Object* object{ layersArray[layerIndex]->at(index) };
		return object;
	}
	else
		return nullptr;
}

ObjectIndex Scene::GetObjectIndex(LayerIndex layerIndex, const Object* object) const noexcept
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

ObjectIndex Scene::MoveObjectLayer(
	LayerIndex srcLayerIndex, 
	ObjectIndex objIndex, 
	LayerIndex destLayerIndex)
{
	Object* object{ GetObject(srcLayerIndex, objIndex) };
	if (object)
	{
		DeleteObject(srcLayerIndex, objIndex);
		return AddObject(destLayerIndex, object);
	}
	else
		return 0;
}

ObjectIndex Scene::MoveObjectLayer(Object* object, LayerIndex destinationLayerIndex)
{
	LayerIndex srcLayerIndex{ object->GetLayerIndex() };
	return MoveObjectLayer(srcLayerIndex, GetObjectIndex(srcLayerIndex, object), destinationLayerIndex);
}

const LayerVector* Scene::GetLayerVector(LayerIndex layerIndex) const noexcept
{
	return layersArray[layerIndex];
}

Collision Scene::GetCollidedObject(int x, int y)
{
	for (auto layerIt{ layersArray.rbegin() }; layerIt != layersArray.rend(); ++layerIt)
	{
		LayerVector* layer{ *layerIt };
		for (auto objectIt{ layer->rbegin() }; objectIt != layer->rend(); ++objectIt)
		{
			Object* object{ *objectIt };
			Collision collision{ object->IsColliding(
				static_cast<float>(x), 
				static_cast<float>(y)
			) };
			if (collision.type != CollisionType::NO_COLLISION)
				return collision;
		}
	}

	return Collision{};
}

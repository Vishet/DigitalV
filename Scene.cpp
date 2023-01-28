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

void Scene::AddObject(size_t layerIndex, Object* object) noexcept
{
	layersArray[layerIndex]->push_back(object);
}

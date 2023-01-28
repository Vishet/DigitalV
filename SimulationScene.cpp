#include "SimulationScene.h"

#include "CrateObject.h"

void SimulationScene::Load()
{
	AddObject(0u, new CrateObject());
}

void SimulationScene::Update()
{

}
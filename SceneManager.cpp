#include "SceneManager.h"
#include "Graphics.h"

SceneManager::~SceneManager()
{
	currentScene->Unload();
}

void SceneManager::LoadScene(Scene* scene) noexcept
{
	currentScene = scene;
	currentScene->Load();
}

void SceneManager::KeyInput(const Keyboard::Event& keyEvent) noexcept
{
	currentScene->KeyInput(keyEvent);
}

void SceneManager::MouseInput(const Mouse::Event& mouseEvent) noexcept
{
	currentScene->MouseInput(mouseEvent);
}

void SceneManager::UpdateScene() noexcept
{
	currentScene->Update();
}

void SceneManager::RenderScene() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	graphics->BeginDraw();
	currentScene->Render();
	graphics->EndDraw();
}
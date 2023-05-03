#include "SceneManager.h"
#include "Graphics.h"

Scene* SceneManager::currentScene{};

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
	currentScene->OnKeyInput(keyEvent);
}

void SceneManager::MouseInput(const Mouse::Event& mouseEvent) noexcept
{
	currentScene->OnMouseInput(mouseEvent);
}

void SceneManager::UpdateScene() noexcept
{
	currentScene->Update();
}

void SceneManager::RenderScene() const
{
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	graphics->BeginDraw(0.0f, 0.0f, 0.0f);
	currentScene->Render();
	graphics->EndDraw();
}

Scene* SceneManager::GetCurrentScene() noexcept
{
	if (currentScene)
		return currentScene;
}

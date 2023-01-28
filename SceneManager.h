#pragma once

#include "Scene.h"
#include "Keyboard.h"
#include "Mouse.h"

class SceneManager
{
private:
	Scene* currentScene{};

public:
	SceneManager() = default;
	~SceneManager();

	SceneManager(const SceneManager&) = delete;
	SceneManager(const SceneManager&&) = delete;
	SceneManager operator=(const SceneManager&) = delete;
	SceneManager operator=(const SceneManager&&) = delete;

	void LoadScene(Scene* scene) noexcept;
	void UpdateScene() noexcept;
	void RenderScene() const;
};


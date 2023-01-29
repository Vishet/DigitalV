#pragma once

#include "MainWindow.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "SceneManager.h"
#include <optional>

class App
{
private:
	Keyboard* keyboard{ Keyboard::GetKeyboardPointer() };
	Mouse* mouse{ Mouse::GetMousePointer() };
	MainWindow mainWindow{ keyboard, mouse };
	Graphics* graphics{ Graphics::GetGraphicsPointer() };
	SceneManager sceneManager{};

public:
	App(const App&) = delete;
	App(const App&&) = delete;
	App operator=(const App&) = delete;
	App operator=(const App&&) = delete;

	App();
	~App();

	int Run();

private:
	std::optional<int> ProcessMessages() noexcept;
	void Update();
	void Render() const;
};


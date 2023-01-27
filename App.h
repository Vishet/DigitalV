#pragma once

#include "MainWindow.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <optional>

class App
{
private:
	Keyboard keyboard{};
	Mouse mouse{};
	MainWindow mainWindow{ &keyboard, &mouse };

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


#pragma once

#include "GenericWindow.h"

class MainWindow : public GenericWindow
{
public:
	MainWindow(const MainWindow&) = delete;
	MainWindow(const MainWindow&&) = delete;
	MainWindow operator=(const MainWindow&) = delete;
	MainWindow operator=(const MainWindow&&) = delete;

	MainWindow(Keyboard* keyboard, Mouse* mouse) noexcept;
	~MainWindow() noexcept;

private:
	LRESULT WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) noexcept override;
};


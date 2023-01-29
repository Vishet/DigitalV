#include "MainWindow.h"

MainWindow::MainWindow(Keyboard* keyboard, Mouse* mouse) noexcept :
	GenericWindow("DigitalV", 1280, 720, false, WS_OVERLAPPED | WS_SYSMENU, keyboard, mouse)
{
}

MainWindow::~MainWindow() noexcept
{
}

LRESULT MainWindow::WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(windowHandle, message, wParam, lParam);
	}

	return 0;
}



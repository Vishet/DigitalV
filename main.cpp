#include "App.h"
#include "Exception.h"
#include <windows.h>
#include <memory>

int APIENTRY wWinMain(HINSTANCE instanceHandle, HINSTANCE hPrev, PWSTR cmdLine, int cmdshow) 
{
	try
	{
		auto app{ std::make_unique<App>() };
		return app->Run();
	}
	catch (const Exception& e)
	{
		MessageBox(nullptr, e.what(), "Error!", MB_OK | MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Error!", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details avaliable!", "Undentified error!", MB_OK | MB_ICONERROR);
	}

	return -1;
}
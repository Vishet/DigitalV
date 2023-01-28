#include "App.h"

#include "SimulationScene.h"

App::App()
{
	mainWindow.Initialize();
	graphics->Initialize(mainWindow.GetWindowHandle());

	mainWindow.Show();

	sceneManager.LoadScene(new SimulationScene());
}

App::~App()
{

}

int App::Run()
{
	while (true)
	{
		if (const auto returnCode{ ProcessMessages() })
			return *returnCode;

		Update();
		Render();
	}
}

std::optional<int> App::ProcessMessages() noexcept
{
	MSG message{};

	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
			return static_cast<int>(message.wParam);

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return {};
}

void App::Update()
{
	while (auto keyEvent{ keyboard.ReadKey() })
	{
		switch (keyEvent->GetCode())
		{
		case VK_S:
			if (!keyEvent->IsPressing())
			{
				MessageBox(NULL, "You've pressed the key 'S'.", "Keyboard Event", MB_OK);
			}
			break;
		}
	}

	while (auto mouseEvent{ mouse.ReadEvent() })
	{
		switch (mouseEvent->GetType())
		{
		case Mouse::Event::Type::LMBReleased:
			if (keyboard.IsKeyDown(VK_W)) 
			{
				MessageBox(NULL, "You've Clicked with the W key pressed.", "Mouse Event", MB_OK);
			}
			break;
		}
	}

	sceneManager.UpdateScene();
}

void App::Render() const
{
	sceneManager.RenderScene();
}

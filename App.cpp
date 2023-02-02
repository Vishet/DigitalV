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
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
			return static_cast<int>(message.wParam);
	}

	return {};
}

void App::Update()
{
	while (auto keyEvent{ keyboard->ReadKey() })
	{
		sceneManager.KeyInput(*keyEvent);

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

	while (auto mouseEvent{ mouse->ReadEvent() })
	{
		sceneManager.MouseInput(*mouseEvent);

		switch (mouseEvent->GetType())
		{
		case Mouse::Event::Type::LMBReleased:
			if (keyboard->IsKeyDown(VK_W)) 
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

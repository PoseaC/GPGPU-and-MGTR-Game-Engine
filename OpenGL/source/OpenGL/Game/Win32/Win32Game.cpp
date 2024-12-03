#include <OpenGL/Game/Game.h>
#include <OpenGL/Window/Window.h>
#include <OpenGL/Graphics/GraphicsEngine.h>
#include <Windows.h>

void Game::Run()
{
	OnCreate();
	MSG msg;
	while (m_isRunning)
	{
		MSG msg = {};
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				Quit();
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}

		Sleep(1);
		OnUpdateInternal();
	}
}

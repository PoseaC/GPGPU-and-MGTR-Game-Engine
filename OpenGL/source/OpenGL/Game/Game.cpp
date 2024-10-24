#include "OpenGL/Game/Game.h"
#include "OpenGL/Window/Window.h"
#include "Windows.h"

Game::Game()
{
	m_display = std::unique_ptr<Window> (new Window(1200, 700));
}

Game::~Game()
{
}

void Game::run()
{
	MSG msg;
	while (m_is_running && !m_display->IsClosed())
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		Sleep(1);
	}
}

void Game::quit()
{
	m_is_running = false;
}

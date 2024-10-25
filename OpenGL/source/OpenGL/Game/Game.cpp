#include <OpenGL/Game/Game.h>
#include <OpenGL/Window/Window.h>
#include <OpenGL/Graphics/GraphicsEngine.h>

Game::Game()
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<Window>(1200, 700);

	m_display->makeCurrentContext();
}

Game::~Game()
{
}

void Game::OnCreate()
{
}

void Game::OnUpdate()
{
	m_graphicsEngine->clear(Vector4(1, 0, 0, 1));
	m_display->present(false);
}

void Game::OnQuit()
{
}

void Game::Quit()
{
	m_isRunning = false;
	OnQuit();
}

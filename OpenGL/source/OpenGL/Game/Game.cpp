#include <OpenGL/Game/Game.h>
#include <OpenGL/Window/Window.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/UniformBuffer.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Vector2.h>
#include <OpenGL/Entity/EntitySystem.h>
#include <OpenGL/Entity/Entity.h>
#include <OpenGL/InputSystem/InputSystem.h>
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


Game::Game()
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<Window>(1200, 700);
	m_entitySystem = std::make_unique<EntitySystem>();
	m_inputSystem = std::make_unique<InputSystem>();

	m_display->makeCurrentContext();

	m_graphicsEngine->setViewport(m_display->getInnerSize());
	m_previousTime = std::chrono::system_clock::now();
}

Game::~Game()
{
}

void Game::OnCreate()
{
	m_display->makeCurrentContext();
	m_graphicsEngine->setFaceCulling(CullType::BackFace);
	m_graphicsEngine->setWindingOrder(WindingOrder::Clockwise);

	m_graphicsEngine->m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
	});
	m_graphicsEngine->m_projection.setIdentity();
	m_graphicsEngine->m_view.setIdentity();
	
}

void Game::OnUpdateInternal()
{
	if (!m_display->m_focused)
		return;

	computeDeltaTime();
	OnUpdate(m_deltaTime);
	m_entitySystem->update(m_deltaTime);

	auto displaySize = m_display->getInnerSize();
	m_graphicsEngine->Clear(Vector4(0, 0, 0, 1));

	float lightColors[9 * 3];
	for (int i = 0; i < 9; i++) {
		lightColors[i * 3 + 0] = m_pointLightsColors[i].m_x;
		lightColors[i * 3 + 1] = m_pointLightsColors[i].m_y;
		lightColors[i * 3 + 2] = m_pointLightsColors[i].m_z;
	}

	float lightPositions[9 * 3];
	for (int i = 0; i < 9; i++) {
		lightPositions[i * 3 + 0] = m_pointLightsPositions[i].m_x;
		lightPositions[i * 3 + 1] = m_pointLightsPositions[i].m_y;
		lightPositions[i * 3 + 2] = m_pointLightsPositions[i].m_z;
	}
	m_graphicsEngine->drawEntities(m_entitySystem->m_entities, 9, lightPositions, lightColors, displaySize);

	m_display->present(false);
	m_graphicsEngine->CheckGLError("Frame Presentation");
}

void Game::OnQuit()
{
}

void Game::Quit()
{
	m_isRunning = false;
	OnQuit();
}

EntitySystem* Game::getEntitySystem()
{
	return m_entitySystem.get();
}

void Game::computeDeltaTime()
{
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();

	elapsedSeconds = currentTime - m_previousTime;
	m_previousTime = currentTime;

	m_deltaTime = (float)elapsedSeconds.count();

	m_frameTimer += m_deltaTime;

	if (m_frameTimer > 1)
	{
		std::cout << "Entities: " << m_entitySystem->m_entities.size() << "; FPS: " << m_framerate << std::endl;
		m_framerate = 0;
		m_frameTimer = 0;
	}

	m_framerate += 1;
}

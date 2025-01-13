#include <OpenGL/Game/Game.h>
#include <OpenGL/Window/Window.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/UniformBuffer.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <OpenGL/Graphics/GraphicsEngine.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Vector2.h>
#include <OpenGL/Entity/EntitySystem.h>
#include <OpenGL/Entity/Entity.h>
#include <OpenGL/InputSystem/InputSystem.h>
#include <Windows.h>

struct UniformData
{
	Mat4 world;
	Mat4 projection;
	Mat4 view;
};

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
	m_world.setIdentity();
	m_projection.setIdentity();
	m_view.setIdentity();
}

Game::~Game()
{
}

void Game::OnCreate()
{
	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
	});

	ShaderProgramDesc shaderDesc = {
		L"Assets/Shaders/BasicShader.vert",
		L"Assets/Shaders/BasicShader.frag"
	};
	m_shader = m_graphicsEngine->createShaderProgram(shaderDesc);

	m_shader->setUniformBufferSlot("UniformData", 0);
	m_graphicsEngine->setFaceCulling(CullType::BackFace);
	m_graphicsEngine->setWindingOrder(WindingOrder::Clockwise);
	m_graphicsEngine->setShaderProgram(m_shader);
}

void Game::OnUpdateInternal()
{
	if (!m_display->m_focused)
		return;

	computeDeltaTime();

	OnUpdate(m_deltaTime);
	m_entitySystem->update(m_deltaTime);

	m_projection.setIdentity();
	auto displaySize = m_display->getInnerSize();
	//m_projection.setOrtho(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f);
	m_projection.setPerspectiveFov(1.57f, ((float) displaySize.width /(float) displaySize.height), 0.1f, 100.0f);

	UniformData data = { m_world, m_projection, m_view };
	m_uniform->setData(&data);

	m_graphicsEngine->Clear(Vector4(0, 0, 0, 1));
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);

	for (auto& e : m_entitySystem->m_entities)
	{
		VertexArrayObjectPtr polygonVAO = m_graphicsEngine->createVertexArrayObject(
			VertexBufferDesc(
				(void*)e->m_vertices.data(),
				sizeof(Vertex),
				e->m_vertices.size(),

				e->m_vertexAttribs.data(),
				e->m_vertexAttribs.size()
			),
			IndexBufferDesc(
				(void*)e->m_indicesList.data(),
				e->m_indicesList.size() * sizeof(int)
			)
		);

		m_graphicsEngine->setVertexArrayObject(polygonVAO);
		m_graphicsEngine->drawIndexedTriangles(TriangleType::TriangleList, e->m_indicesList.size());
	}

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
}

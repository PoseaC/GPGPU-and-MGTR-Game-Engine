#include <OpenGL/Game/Game.h>
#include <OpenGL/Window/Window.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <OpenGL/Graphics/GraphicsEngine.h>

Game::Game()
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<Window>(1200, 700);

	m_display->makeCurrentContext();

	m_graphicsEngine->SetViewport(m_display->getInnerSize());
}

Game::~Game()
{
}

void Game::OnCreate()
{
	const float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.5f, -0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	VertexAttribute attribsList[] = {
		3, //position
		3  //color
	};

	m_triangleVAO = m_graphicsEngine->createVertexArrayObject({
		(void*)triangleVertices,
		sizeof(float) * (3 + 3),
		3,
		attribsList,
		2
	});

	ShaderProgramDesc shaderDesc = {
		L"Assets/Shaders/BasicShader.vert",
		L"Assets/Shaders/BasicShader.frag"
	};
	m_shader = m_graphicsEngine->createShaderProgram(shaderDesc);
}

void Game::OnUpdate()
{
	m_graphicsEngine->Clear(Vector4(0, 0, 0, 1));

	m_graphicsEngine->setVertexArrayObject(m_triangleVAO);
	m_graphicsEngine->setShaderProgram(m_shader);
	m_graphicsEngine->drawTriangles(m_triangleVAO->getVertexBufferSize(), 0);

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

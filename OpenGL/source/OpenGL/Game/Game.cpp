#include <OpenGL/Game/Game.h>
#include <OpenGL/Window/Window.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/UniformBuffer.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <OpenGL/Graphics/GraphicsEngine.h>
#include <OpenGL/Math/Mat4.h>

struct UniformData
{
	Mat4 world;
};

Game::Game()
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<Window>(1200, 700);

	m_display->makeCurrentContext();

	m_graphicsEngine->SetViewport(m_display->getInnerSize());
	m_previousTime = std::chrono::system_clock::now();
}

Game::~Game()
{
}

void Game::OnCreate()
{
	const float polygonVertices[] = {
		-0.5f, -0.5f, 0.0f,
		1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.5f, -0.5f, 0.0f,
		0.0f, 0.0f, 1.0f,

		0.5f, 0.5f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	VertexAttribute attribsList[] = {
		3, //position
		3  //color
	};

	m_polygonVAO = m_graphicsEngine->createVertexArrayObject({
		(void*)polygonVertices,
		sizeof(float) * (3 + 3),
		4,
		attribsList,
		2
	});

	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
	});

	ShaderProgramDesc shaderDesc = {
		L"Assets/Shaders/BasicShader.vert",
		L"Assets/Shaders/BasicShader.frag"
	};
	m_shader = m_graphicsEngine->createShaderProgram(shaderDesc);

	m_shader->setUniformBufferSlot("UniformData", 0);
}

void Game::OnUpdate()
{
	computeDeltaTime();

	m_animationStep += 1.0f * m_deltaTime;
	float currentScale = abs(sin(m_animationStep));

	Mat4 world, temp;
	world.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_animationStep);
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_animationStep);
	world *= temp;

	temp.setIdentity();
	temp.setRotationZ(m_animationStep);
	world *= temp;

	UniformData data = { world };
	m_uniform->setData(&data);

	m_graphicsEngine->Clear(Vector4(0, 0, 0, 1));

	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);
	m_graphicsEngine->setShaderProgram(m_shader);
	m_graphicsEngine->drawTriangles(TriangleStrip, m_polygonVAO->getVertexBufferSize(), 0);

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

void Game::computeDeltaTime()
{
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();

	elapsedSeconds = currentTime - m_previousTime;
	m_previousTime = currentTime;

	m_deltaTime = (float)elapsedSeconds.count();
}

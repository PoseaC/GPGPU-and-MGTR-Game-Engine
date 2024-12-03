#include <OpenGL/Game/Game.h>
#include <OpenGL/Window/Window.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/UniformBuffer.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <OpenGL/Graphics/GraphicsEngine.h>
#include <OpenGL/Math/Mat4.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Vector2.h>
#include <OpenGL/Entity/EntitySystem.h>

struct UniformData
{
	Mat4 world;
	Mat4 projection;
};

struct Vertex
{
	Vector3 position;
	Vector2 texcoord;
};

Game::Game()
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<Window>(1200, 700);
	m_entitySystem = std::make_unique<EntitySystem>();

	m_display->makeCurrentContext();

	m_graphicsEngine->setViewport(m_display->getInnerSize());
	m_previousTime = std::chrono::system_clock::now();
}

Game::~Game()
{
}

void Game::OnCreate()
{
	Vector3 positionsList[] = 
	{
		//front face
		Vector3(-0.5f, -0.5f, -0.5f),
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.5f, -0.5f, -0.5f),

		//back face
		Vector3(0.5f, -0.5f, 0.5f),
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, -0.5f, 0.5f),
	};

	unsigned int indicesList[] =
	{
		//front
		0, 1, 2,
		2, 3, 0,

		//back
		4, 5, 6,
		6, 7, 4,

		//top
		8, 9, 10,
		10, 11, 8,

		//bottom
		12, 13, 14,
		14, 15, 12,

		//right
		16, 17, 18,
		18, 19, 16,

		//left
		20, 21, 22,
		22, 23, 20
	};
	
	Vector2 texcoordsList[] =
	{
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,0),
		Vector2(1,1),
	};

	Vertex verticesList[] =
	{
		//front face
		{ positionsList[0], texcoordsList[1] },
		{ positionsList[1], texcoordsList[0] },
		{ positionsList[2], texcoordsList[2] },
		{ positionsList[3], texcoordsList[3] },

		//back face
		{ positionsList[4], texcoordsList[1] },
		{ positionsList[5], texcoordsList[0] },
		{ positionsList[6], texcoordsList[2] },
		{ positionsList[7], texcoordsList[3] },

		//top face
		{ positionsList[1], texcoordsList[1] },
		{ positionsList[6], texcoordsList[0] },
		{ positionsList[5], texcoordsList[2] },
		{ positionsList[2], texcoordsList[3] },

		//bottom face
		{ positionsList[7], texcoordsList[1] },
		{ positionsList[0], texcoordsList[0] },
		{ positionsList[3], texcoordsList[2] },
		{ positionsList[4], texcoordsList[3] },

		//right face
		{ positionsList[3], texcoordsList[1] },
		{ positionsList[2], texcoordsList[0] },
		{ positionsList[5], texcoordsList[2] },
		{ positionsList[4], texcoordsList[3] },

		//left face
		{ positionsList[7], texcoordsList[1] },
		{ positionsList[6], texcoordsList[0] },
		{ positionsList[1], texcoordsList[2] },
		{ positionsList[0], texcoordsList[3] },
	};

	VertexAttribute attribsList[] = 
	{
		sizeof(Vector3) / sizeof(float), //position
		sizeof(Vector2) / sizeof(float) //texcoord
	};

	m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
		{
			(void*)verticesList,
			sizeof(Vertex),
			sizeof(verticesList) / sizeof(Vertex),

			attribsList,
			sizeof(attribsList) / sizeof(VertexAttribute)
		},

		{
			(void*) indicesList,
			sizeof(indicesList)
		}
	);

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

void Game::OnUpdateInternal()
{
	computeDeltaTime();

	OnUpdate(m_deltaTime);
	m_entitySystem->update(m_deltaTime);

	m_animationStep += 0.5f * m_deltaTime;
	float currentScale = abs(sin(m_animationStep));

	Mat4 world, projection, temp;
	projection.setIdentity();
	world.setIdentity();
	temp.setIdentity();

	temp.setRotationX(0.25);
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_animationStep);
	world *= temp;

	//temp.setIdentity();
	//temp.setRotationZ(m_animationStep);
	//world *= temp;

	auto displaySize = m_display->getInnerSize();
	projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f);

	UniformData data = { world, projection };
	m_uniform->setData(&data);

	m_graphicsEngine->Clear(Vector4(0, 0, 0, 1));

	m_graphicsEngine->setFaceCulling(CullType::BackFace);
	m_graphicsEngine->setWindingOrder(WindingOrder::Clockwise);
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);
	m_graphicsEngine->setShaderProgram(m_shader);
	m_graphicsEngine->drawIndexedTriangles(TriangleType::TriangleList, 36);

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

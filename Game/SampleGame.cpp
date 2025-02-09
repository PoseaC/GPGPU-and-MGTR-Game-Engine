#include "SampleGame.h"
#include <OpenGL/InputSystem/InputSystem.h>

SampleGame::SampleGame()
{
}

SampleGame::~SampleGame()
{
}

void SampleGame::OnCreate()
{
	Game::OnCreate();
	m_inputSystem->AddListener(this);
	m_player = std::make_unique<Player>(Vector3(1, 1, 1));
	m_entitySystem->registerEntity(m_player.get());
	m_inputSystem->AddListener(m_player.get());
	m_player->setPosition(Vector3(2, 10, 2));

	Entity* floor = new Entity(Vector3(20, 1, 20));
	m_entitySystem->registerEntity(floor);
	floor->m_kinematic = true;
	floor->m_mass = 10000;

	Entity* testCube = new Entity(Vector3(1, 1, 1));
	m_entitySystem->registerEntity(testCube);
	testCube->setScale(Vector3(1, 1, 1));
	testCube->setPosition(Vector3(5, 5, 1));

	//visualize light positions
	for (int i = 0; i < sizeof(m_pointLightsPositions) / sizeof(Vector3); i++)
	{
		Entity* light = new Entity(Vector3(0.1, 0.1, 0.1));
		m_entitySystem->registerEntity(light);
		light->m_kinematic = true;
		light->m_trigger = true;
		light->setPosition(m_pointLightsPositions[i]);
	}

	m_cameraPos.setIdentity();
	m_cameraPos.setTranslation(Vector3(0, 5, -10));
}

void SampleGame::OnUpdate(float deltaTime)
{
	m_inputSystem->Update();
	
	Mat4 tempCameraPos, temp;
	tempCameraPos.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_cameraRotationX);
	tempCameraPos *= temp;

	temp.setIdentity();
	temp.setRotationY(m_cameraRotationY);
	tempCameraPos *= temp;

	Vector3 newPos = m_cameraPos.getTranslation() + tempCameraPos.getZDirection() * m_cameraMovingForward
												  + tempCameraPos.getXDirection() * m_cameraMovingRight
												  + Vector3(0, 1, 0) * m_cameraMovingUp;

	tempCameraPos.setTranslation(newPos);
	m_cameraPos = tempCameraPos;
	tempCameraPos.inverse();

	m_graphicsEngine->setViewMatrix(tempCameraPos);

	m_graphicsEngine->setEyePosition(m_cameraPos.getTranslation());
}

void SampleGame::OnKeyDown(int keycode)
{
	if (keycode == 'W')
		m_cameraMovingForward = m_cameraSpeed * m_deltaTime;
	if (keycode == 'S')
		m_cameraMovingForward = -m_cameraSpeed * m_deltaTime;
	if (keycode == 'D')
		m_cameraMovingRight = m_cameraSpeed * m_deltaTime;
	if (keycode == 'A')
		m_cameraMovingRight = -m_cameraSpeed * m_deltaTime;
	if (keycode == 'E')
		m_cameraMovingUp = m_cameraSpeed * m_deltaTime;
	if (keycode == 'Q')
		m_cameraMovingUp = -m_cameraSpeed * m_deltaTime;
	if (keycode == 'G' && m_canSpawn)
		SpawnObjects();
	if (keycode == 'F' && m_canFreezeSimulation)
	{
		m_entitySystem->m_simulationFreeze = !m_entitySystem->m_simulationFreeze;
		m_canFreezeSimulation = false;
	}
}

void SampleGame::OnKeyUp(int keycode)
{
	if (keycode == 'W' || keycode == 'S')
		m_cameraMovingForward = 0;
	if (keycode == 'A' || keycode == 'D')
		m_cameraMovingRight = 0;
	if (keycode == 'Q' || keycode == 'E')
		m_cameraMovingUp = 0;
	if (keycode == 'G')
		m_canSpawn = true;
	if (keycode == 'F')
		m_canFreezeSimulation = true;
}

void SampleGame::SpawnObjects()
{
	m_canSpawn = false;
	for (int i = 0; i < 100; i++)
	{
		Entity* obj = new Entity(Vector3(1, 1, 1));
		m_entitySystem->registerEntity(obj);
		Vector3 position = Vector3(rand() % 20, rand() % 20, rand() % 20) - Vector3(10, -5, 10);
		Vector3 force = Vector3(rand() % 3, rand() % 3, rand() % 3) - Vector3(1.5f, 1.5f, 1.5f);
		obj->setPosition(position);
		obj->AddForce(force, ForceType::VELOCITY_CHANGE);
		obj->m_mesh.m_color = Vector3(rand() % 256 / 255.0f, rand() % 256 / 255.0f, rand() % 256 / 255.0f);
	}
}

void SampleGame::OnMouseMove(const Point& deltaMousePos)
{
	m_cameraRotationY += deltaMousePos.m_x * m_deltaTime * 0.5f;
	m_cameraRotationX += deltaMousePos.m_y * m_deltaTime * 0.5f;
}

void SampleGame::OnMouseButtonDown(const Point& deltaMousePos, int button)
{

}

void SampleGame::OnMouseButtonUp(const Point& deltaMousePos, int button)
{

}

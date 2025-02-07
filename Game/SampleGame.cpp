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
	m_player = getEntitySystem()->createEntity<Player>();
	m_inputSystem->AddListener(m_player);

	StaticEntity* floor = getEntitySystem()->createEntity<StaticEntity>();
	m_player->setPosition(Vector3(0.5, 5, 0.5));
	floor->setPosition(Vector3(0, 0, 0));

	m_cameraPos.setIdentity();
	m_cameraPos.setTranslation(Vector3(0, 2, -2));
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

	m_view = tempCameraPos;

	m_graphicsEngine->setEyePosition(m_shader, m_cameraPos.getTranslation());
}

void SampleGame::OnKeyDown(int keycode)
{
	if (keycode == 'W')
		m_cameraMovingForward = m_deltaTime;
	else if (keycode == 'S')
		m_cameraMovingForward = -m_deltaTime;
	else if (keycode == 'D')
		m_cameraMovingRight = m_deltaTime;
	else if (keycode == 'A')
		m_cameraMovingRight = -m_deltaTime;
	else if (keycode == 'E')
		m_cameraMovingUp = m_deltaTime;
	else if (keycode == 'Q')
		m_cameraMovingUp = -m_deltaTime;
	else if (keycode == 'G' && m_canSpawn)
		SpawnObjects();
}

void SampleGame::OnKeyUp(int keycode)
{
	if (keycode == 'W' || keycode == 'S')
		m_cameraMovingForward = 0;
	else if (keycode == 'A' || keycode == 'D')
		m_cameraMovingRight = 0;
	else if (keycode == 'Q' || keycode == 'E')
		m_cameraMovingUp = 0;
	else if (keycode == 'G')
		m_canSpawn = true;
}

void SampleGame::SpawnObjects()
{
	m_canSpawn = false;
	for (int i = 0; i < 10; i++)
	{
		StaticEntity* obj = getEntitySystem()->createEntity<StaticEntity>();
		obj->setPosition(Vector3(rand() % 10, rand() % 10, rand() % 10));
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

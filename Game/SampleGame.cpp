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
	m_player->setPosition(Vector3(0, 3, 0));

	m_cameraPos.setIdentity();
	m_cameraPos.setTranslation(Vector3(0, 0, -2));
}

void SampleGame::OnUpdate(float deltaTime)
{
	m_inputSystem->Update();
	
	Mat4 temp;
	temp.setIdentity();
	m_world.setIdentity();
	m_transform.setIdentity();

	m_transform.setRotationX(m_cameraRotationX);
	temp *= m_transform;

	m_transform.setIdentity();
	m_transform.setRotationY(m_cameraRotationY);
	temp *= m_transform;

	Vector3 newPos = m_cameraPos.getTranslation() + temp.getZDirection() * m_cameraMovingForward
												  + temp.getXDirection() * m_cameraMovingRight
												  + Vector3(0, 1, 0) * m_cameraMovingUp;

	temp.setTranslation(newPos);
	m_cameraPos = temp;
	temp.inverse();

	m_view = temp;
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
}

void SampleGame::OnKeyUp(int keycode)
{
	if (keycode == 'W' || keycode == 'S')
		m_cameraMovingForward = 0;
	else if (keycode == 'A' || keycode == 'D')
		m_cameraMovingRight = 0;
	else if (keycode == 'Q' || keycode == 'E')
		m_cameraMovingUp = 0;
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

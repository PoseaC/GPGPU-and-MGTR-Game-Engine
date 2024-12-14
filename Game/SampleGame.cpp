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
}

void SampleGame::OnUpdate(float deltaTime)
{
	m_inputSystem->Update();

	m_world.setIdentity();
	m_transform.setIdentity();

	m_transform.setRotationX(0.25);
	m_world *= m_transform;

	m_transform.setIdentity();
	m_transform.setRotationY(m_animationStep);
	m_world *= m_transform;
}

void SampleGame::OnKeyDown(int keycode)
{
	if (keycode == 'W')
		m_animationStep += m_deltaTime;
	else if (keycode == 'S')
		m_animationStep -= m_deltaTime;
}

void SampleGame::OnKeyUp(int keycode)
{

}

void SampleGame::OnMouseMove(const Point& deltaMousePos)
{
	//m_animationStep += deltaMousePos.m_x * m_deltaTime;
}

void SampleGame::OnMouseButtonDown(const Point& deltaMousePos, int button)
{
	m_animationStep = 0.5;
}

void SampleGame::OnMouseButtonUp(const Point& deltaMousePos, int button)
{
	m_animationStep = 0;
}

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
	m_inputSystem.AddListener(this);
	m_player = getEntitySystem()->createEntity<Player>();
}

void SampleGame::OnUpdate(float deltaTime)
{
	m_inputSystem.Update();
	float currentScale = abs(sin(m_animationStep));

	Mat4 temp;
	m_world.setIdentity();
	temp.setIdentity();

	temp.setRotationX(0.25);
	m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_animationStep);
	m_world *= temp;
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

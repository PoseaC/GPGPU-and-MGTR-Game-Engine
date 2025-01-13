#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::OnCreate()
{
	Entity::OnCreate();
}

void Player::OnUpdate(float deltaTime)
{
	Entity::OnUpdate(deltaTime);
	m_deltaTime = deltaTime;
	m_position = Vector3(m_position.m_x + m_movingRight, m_position.m_y + m_movingUp, m_position.m_z + m_movingForward);
}

void Player::OnKeyDown(int keycode)
{
	if (keycode == 'I')
		m_movingForward = m_deltaTime;
	else if (keycode == 'K')
		m_movingForward = -m_deltaTime;
	else if (keycode == 'L')
		m_movingRight = m_deltaTime;
	else if (keycode == 'J')
		m_movingRight = -m_deltaTime;
	else if (keycode == 'O')
		m_movingUp = m_deltaTime;
	else if (keycode == 'U')
		m_movingUp = -m_deltaTime;
}

void Player::OnKeyUp(int keycode)
{
	if (keycode == 'I' || keycode == 'K')
		m_movingForward = 0;
	else if (keycode == 'J' || keycode == 'L')
		m_movingRight = 0;
	else if (keycode == 'U' || keycode == 'O')
		m_movingUp = 0;
}

void Player::OnMouseMove(const Point& deltaMousePos)
{
}

void Player::OnMouseButtonDown(const Point& deltaMousePos, int button)
{
}

void Player::OnMouseButtonUp(const Point& deltaMousePos, int button)
{
}

void Player::OnCollisionStart(Entity* collider)
{
	std::cout << "collision start" << std::endl;
}

void Player::OnCollisionEnd(Entity* collider)
{
	std::cout << "collision end" << std::endl;
}

void Player::OnCollisionStay(Entity* collider)
{
	std::cout << "collision stay" << std::endl;
}

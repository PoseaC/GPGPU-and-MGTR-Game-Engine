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
	m_deltaTime = deltaTime;
	float coefficient = 0.0f;

	if (m_applyGravity)
	{
		m_velocity.m_y -= 9.81f * deltaTime;
		coefficient = m_drag;
	}
	else
	{
		coefficient = m_friction;
	}

	m_velocity = m_velocity + m_velocity * (-coefficient * deltaTime);
	m_position = m_position + (m_velocity * deltaTime * 0.5f);
	Entity::OnUpdate(deltaTime);
}

void Player::OnKeyDown(int keycode)
{
	if (keycode == 'Z')
		m_velocity.m_y = 4;
	else if (keycode == 'I')
		m_velocity.m_z = 4;
	else if (keycode == 'K')
		m_velocity.m_z = -4;
	else if (keycode == 'L')
		m_velocity.m_x = 4;
	else if (keycode == 'J')
		m_velocity.m_x = -4;
}

void Player::OnKeyUp(int keycode)
{
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

void Player::OnCollisionStart(Entity* collider, Vector3 collisionNormal)
{
	m_velocity = m_velocity + (m_velocity * collisionNormal * 2 * -m_bounciness);
	std::cout << "collision start" << std::endl;
}

void Player::OnCollisionEnd(Entity* collider)
{
	m_applyGravity = true;
	std::cout << "collision end" << std::endl;
}

void Player::OnCollisionStay(Entity* collider, Vector3 collisionNormal)
{
	if (collisionNormal.m_y == 1 && collider->m_position.m_y < m_position.m_y) 
	{
		m_applyGravity = false;
		m_velocity.m_y = 9.81f * m_deltaTime;
	}
	else
		m_velocity = m_velocity + (m_velocity * collisionNormal * 2 * -m_bounciness);
	
	std::cout << "collision stay" << std::endl;
}

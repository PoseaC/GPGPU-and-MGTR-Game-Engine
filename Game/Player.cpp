#include "Player.h"

void Player::OnCreate()
{
	Entity::OnCreate();
}

void Player::OnUpdate(float deltaTime)
{
	Entity::OnUpdate(deltaTime);
}

void Player::OnKeyDown(int keycode)
{
	if (keycode == 'Z' && !m_jumped)
	{
		AddForce(Vector3(0, 4, 0), ForceType::IMPULSE);
		m_jumped = true;
	}
	if (keycode == 'I')
		AddForce(Vector3(0, 0, 4));
	if (keycode == 'K')
		AddForce(Vector3(0, 0, -4));
	if (keycode == 'L')
		AddForce(Vector3(4, 0, 0));
	if (keycode == 'J')
		AddForce(Vector3(-4, 0, 0));
}

void Player::OnKeyUp(int keycode)
{
	if (keycode == 'Z')
		m_jumped = false;
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

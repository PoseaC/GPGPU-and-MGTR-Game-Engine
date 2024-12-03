#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::OnCreate()
{
	m_entity = getEntitySystem()->createEntity<Entity>();
}

void Player::OnUpdate(float deltaTime)
{
	m_elapsedSeconds += deltaTime;

	if (m_entity && m_elapsedSeconds >= 3.0f)
	{
		m_entity->release();
		m_entity = nullptr;
	}
}

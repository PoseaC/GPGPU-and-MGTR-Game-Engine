#include <OpenGL/Entity/Entity.h>
#include <OpenGL/Entity/EntitySystem.h>
#include <OpenGL/Graphics/GraphicsEngine.h>

void Entity::OnCreate()
{
	m_transform.setIdentity();
	m_position = Vector3(0, 0, 0);
	m_scale = m_boxSize;
}

void Entity::OnUpdate(float deltaTime)
{
	PhysicsUpdate(deltaTime);
	m_transform.setTranslation(m_position);
	m_transform.setScale(m_scale);

	if (m_position.m_y < -50)
		release();
}

void Entity::release()
{
	m_entitySystem->removeEntity(this);
}

EntitySystem* Entity::getEntitySystem()
{
	return m_entitySystem;
}

void Entity::setPosition(Vector3 newPosition)
{
	m_position = newPosition;
}

void Entity::setScale(Vector3 newScale)
{
	m_scale = newScale;
	m_boxSize = newScale;
}

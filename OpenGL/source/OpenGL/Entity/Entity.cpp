#include <OpenGL/Entity/Entity.h>
#include <OpenGL/Entity/EntitySystem.h>

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::release()
{
	m_entitySystem->removeEntity(this);
}

EntitySystem* Entity::getEntitySystem()
{
	return m_entitySystem;
}

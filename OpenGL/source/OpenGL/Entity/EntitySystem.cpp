#include <OpenGL/Entity/EntitySystem.h>
#include <OpenGL/Entity/Entity.h>

EntitySystem::EntitySystem()
{
}

EntitySystem::~EntitySystem()
{
}

bool EntitySystem::registerEntity(Entity* entity)
{
	m_entities.emplace(entity);

	entity->m_entitySystem = this;
	entity->OnCreate();

	return true;
}

void EntitySystem::removeEntity(Entity* entity)
{
	m_entitiesToDestroy.emplace(entity);
}

void EntitySystem::update(float deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities.erase(e);
	}
	m_entitiesToDestroy.clear();

	for (auto& entity : m_entities)
	{
		entity->m_simulationFreeze = m_simulationFreeze;
		entity->OnUpdate(deltaTime);
	}

	for (auto it1 = m_entities.begin(); it1 != m_entities.end(); it1++)
	{
		for (auto it2 = it1; it2 != m_entities.end(); it2++)
		{
			if (it1 != it2)
				(*it1)->CheckOverlap(*it2);
		}
	}
}

#pragma once

#include <map>
#include <memory>
#include <set>

class Entity;
class EntitySystem
{
public:
	EntitySystem();
	~EntitySystem();

	bool registerEntity(Entity* entity);
	bool m_simulationFreeze = false;

private:
	void removeEntity(Entity* entity);
	void update(float deltaTime);

	std::set<Entity*> m_entities;
	std::set<Entity*> m_entitiesToDestroy;

	friend class Entity;
	friend class Game;
};


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

	template <typename T>
	T* createEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity class");
		auto e = new T();

		if (createEntityInternal(e))
			return e;

		return nullptr;
	}

private:
	bool createEntityInternal(Entity* entity);
	void removeEntity(Entity* entity);

	void update(float deltaTime);

	std::set<Entity*> m_entities;
	std::set<Entity*> m_entitiesToDestroy;

	friend class Entity;
	friend class Game;
};


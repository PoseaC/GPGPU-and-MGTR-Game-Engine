#pragma once

class EntitySystem;
class Entity
{
public:
	Entity();
	virtual ~Entity();

	void release();
	EntitySystem* getEntitySystem();

protected:
	virtual void OnCreate() {}
	virtual void OnUpdate(float deltaTime) {}

	size_t m_id = 0;
	EntitySystem* m_entitySystem = nullptr;

	friend class EntitySystem;
};


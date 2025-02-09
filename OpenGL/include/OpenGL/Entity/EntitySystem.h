#pragma once
#include <OpenGL/Math/Vector3.h>
#include <glad/glad.h>
#include <map>
#include <memory>
#include <set>

struct ColliderDataBuffer {
	Vector3 position;
	Vector3 velocity;
	Vector3 boxSize;
	float mass;
	int isKinematic;
	int isTrigger;
	float elasticity;
	float friction;
	float drag;
	float deltaTime;
};

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

	void collisionDetectionCPU();
	void collisionDetectionGPU();

	std::set<Entity*> m_entities;
	std::set<Entity*> m_entitiesToDestroy;
	GLuint m_colliderComputeShader;

	friend class Entity;
	friend class Game;
};


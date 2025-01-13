#pragma once
#include <vector>
#include <set>
#include <Prerequisites.h>
#include <OpenGL/Math/Vector2.h>
#include <OpenGL/Math/Vector3.h>

struct Vertex
{
	Vector3 position;
	Vector2 texcoord;
};

class EntitySystem;
class Entity
{
public:
	Entity();
	virtual ~Entity();

	void release();
	EntitySystem* getEntitySystem();
	void setPosition(Vector3 newPosition);
	void CheckOverlap(Entity* possibleCollider);

	std::vector<Vector3> m_vertexPositions;
	std::vector<unsigned int> m_indicesList;
	std::vector <Vector2> m_textureCoords;
	std::vector<Vertex> m_vertices;
	std::vector<VertexAttribute> m_vertexAttribs;

	Vector3 m_position;

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);
	virtual void OnCollisionStart(Entity* collider) {}
	virtual void OnCollisionEnd(Entity* collider) {}
	virtual void OnCollisionStay(Entity* collider) {}

	EntitySystem* m_entitySystem = nullptr;
	std::set<Entity*> m_collisions;

	friend class EntitySystem;
};


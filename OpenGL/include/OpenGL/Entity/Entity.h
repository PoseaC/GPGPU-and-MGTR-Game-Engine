#pragma once
#include <vector>
#include <set>
#include <Prerequisites.h>
#include <OpenGL/Math/Vector2.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Mat4.h>
#include <OpenGL/Graphics/Texture.h>

struct Vertex
{
	Vector3 position;
	Vector2 texcoord;
	Vector3 normal;
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
	std::vector<Vector3> m_vertexNormals;
	std::vector<unsigned int> m_indicesList;
	std::vector <Vector2> m_textureCoords;
	std::vector<Vertex> m_vertices;
	std::vector<VertexAttribute> m_vertexAttribs;
	Vector3 boundingBoxCornerOffset;

	VertexArrayObjectPtr m_polygonVAO = nullptr;

	Vector3 m_position;
	Vector3 m_color;
	Mat4 m_transform;
	int m_shininess;
	std::unique_ptr<Texture> m_texture;

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);
	virtual void OnCollisionStart(Entity* collider, Vector3 collisionAxis) {}
	virtual void OnCollisionEnd(Entity* collider) {}
	virtual void OnCollisionStay(Entity* collider, Vector3 collisionAxis) {}

	std::set<Entity*> m_collisions;

	EntitySystem* m_entitySystem = nullptr;
	friend class EntitySystem;
};


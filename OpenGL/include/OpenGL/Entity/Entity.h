#pragma once
#include <vector>
#include <set>
#include <Prerequisites.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Mat4.h>
#include <OpenGL/Graphics/Mesh.h>
#include <OpenGL/Physics/Collider.h>

class EntitySystem;
class Entity : public Collider
{
public:
	Entity(Vector3 boxSize) : Collider(boxSize) {}
	Entity(float radius) : Collider(radius) {}
	Entity(float radius, float cylinderHeight) : Collider(radius, cylinderHeight) {}
	~Entity() {}

	void release();
	EntitySystem* getEntitySystem();
	void setPosition(Vector3 newPosition);
	void setScale(Vector3 newScale);
	Mat4 m_transform;
	Mesh m_mesh;

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);

	EntitySystem* m_entitySystem = nullptr;
	friend class EntitySystem;
};


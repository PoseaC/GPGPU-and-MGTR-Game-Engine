#pragma once
#include <Prerequisites.h>
#include <OpenGL/Math/Vector3.h>
#include <unordered_map>

enum class ColliderType
{
	BOX, SPHERE, CYLINDER
};

enum class ForceType
{
	VELOCITY_CHANGE, ACCELERATION, IMPULSE
};

class Collider
{
public:
	Collider(Vector3 boxSize) : m_boxSize(boxSize), m_type(ColliderType::BOX) {}
	Collider(float radius) : m_radius(radius), m_type(ColliderType::SPHERE) {}
	Collider(float radius, float cylinderHeight) : m_radius(radius), m_cylinderHeight(cylinderHeight), m_type(ColliderType::CYLINDER) {}
	~Collider() {}

	void CheckOverlap(Collider* possibleCollider);
	virtual void OnCollisionStart(Collider* collider, Vector3 collisionAxis, bool isReply = false);
	virtual void OnCollisionEnd(Collider* collider, bool isReply = false);
	virtual void OnCollisionStay(Collider* collider, Vector3 collisionAxis, bool isReply = false);
	virtual void OnTriggerEnter(Collider* collider, bool isReply = false);
	virtual void OnTriggerLeave(Collider* collider, bool isReply = false);
	virtual void OnTriggerStay(Collider* collider, bool isReply = false);

	bool m_trigger = false;
	bool m_simulationFreeze = false;
	bool m_kinematic = false;
	float m_gravity = 9.81f;
	float m_elasticity = 0.5f;
	float m_friction = 0.8f;
	float m_drag = 0.6f;
	float m_mass = 1.0f;

	void PhysicsUpdate(float deltaTime);
	void AddForce(Vector3 force, ForceType type = ForceType::ACCELERATION);

protected:
	Vector3 m_velocity;
	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_boxSize;
	float m_cylinderHeight = 0;
	float m_radius = 0;
	float m_dragCoeficitient = 0;
	float m_deltaTime = 0;

private:
	bool BoxToBoxOverlap(Collider* possibleCollider, Vector3& collisionNormal);
	bool BoxToSphereOverlap(Collider* possibleCollider, Vector3& collisionNormal);
	bool BoxToCylinderOverlap(Collider* possibleCollider, Vector3& collisionNormal);
	bool SphereToSphereOverlap(Collider* possibleCollider, Vector3& collisionNormal);
	bool SphereToCylinderOverlap(Collider* possibleCollider, Vector3& collisionNormal);
	bool CylinderToCylinderOverlap(Collider* possibleCollider, Vector3& collisionNormal);
	void PenetrationResolution(Vector3 collisionNormal, float distance);

	std::unordered_map<Collider*, Vector3> m_collisions;
	ColliderType m_type;
};


#include <OpenGL/Physics/Collider.h>

void Collider::CheckOverlap(Collider* possibleCollider)
{
	Vector3 collisionNormal;
	bool isOverlapping = BoxToBoxOverlap(possibleCollider, collisionNormal);

	if (isOverlapping)
	{
		if (m_collisions.find(possibleCollider) != m_collisions.end())
		{
			OnCollisionStay(possibleCollider, m_collisions[possibleCollider]);
		}
		else
		{
			OnCollisionStart(possibleCollider, collisionNormal);
			m_collisions.emplace(possibleCollider, collisionNormal);
		}
	}
	else if (m_collisions.find(possibleCollider) != m_collisions.end())
	{
		OnCollisionEnd(possibleCollider);
		m_collisions.erase(possibleCollider);
	}
}

bool Collider::BoxToBoxOverlap(Collider* possibleCollider, Vector3& collisionNormal)
{
	float epsilon = 0.0001f;
	Vector3 thisTopRightFront = m_position + m_boxSize;
	Vector3 thisBottomLeftBack = m_position - m_boxSize;

	Vector3 colliderTopRightFront = possibleCollider->m_position + possibleCollider->m_boxSize;
	Vector3 colliderBottomLeftBack = possibleCollider->m_position - possibleCollider->m_boxSize;

	bool isOverlapping = (thisTopRightFront.m_x > colliderBottomLeftBack.m_x - epsilon && thisTopRightFront.m_y > colliderBottomLeftBack.m_y - epsilon && thisTopRightFront.m_z > colliderBottomLeftBack.m_z + epsilon) &&
		(thisBottomLeftBack.m_x < colliderTopRightFront.m_x + epsilon && thisBottomLeftBack.m_y < colliderTopRightFront.m_y + epsilon && thisBottomLeftBack.m_z < colliderTopRightFront.m_z - epsilon);

	if (isOverlapping)
	{
		float overlapX = fminf(thisTopRightFront.m_x, colliderTopRightFront.m_x) - fmaxf(thisBottomLeftBack.m_x, colliderBottomLeftBack.m_x);
		float overlapY = fminf(thisTopRightFront.m_y, colliderTopRightFront.m_y) - fmaxf(thisBottomLeftBack.m_y, colliderBottomLeftBack.m_y);
		float overlapZ = fminf(thisTopRightFront.m_z, colliderTopRightFront.m_z) - fmaxf(thisBottomLeftBack.m_z, colliderBottomLeftBack.m_z);
		float distance = 0;

		if (overlapX < overlapY)
		{
			if (overlapX < overlapZ)
			{
				float direction = m_position.m_x < possibleCollider->m_position.m_x ? -1 : 1;
				collisionNormal = Vector3(direction, 0, 0);
				distance = overlapX;
			}
			else
			{
				float direction = m_position.m_z < possibleCollider->m_position.m_z ? -1 : 1;
				collisionNormal = Vector3(0, 0, direction);
				distance = overlapZ;
			}
		}
		else
		{
			float direction = m_position.m_y < possibleCollider->m_position.m_y ? -1 : 1;
			collisionNormal = Vector3(0, direction, 0);
			distance = overlapY;
		}

		PenetrationResolution(collisionNormal, distance);
		possibleCollider->PenetrationResolution(-collisionNormal, distance);

		return true;
	}

	return false;
}

bool Collider::BoxToSphereOverlap(Collider* possibleCollider, Vector3& collisionNormal)
{
	return false;
}

bool Collider::BoxToCylinderOverlap(Collider* possibleCollider, Vector3& collisionNormal)
{
	return false;
}

bool Collider::SphereToSphereOverlap(Collider* possibleCollider, Vector3& collisionNormal)
{
	return false;
}

bool Collider::SphereToCylinderOverlap(Collider* possibleCollider, Vector3& collisionNormal)
{
	return false;
}

bool Collider::CylinderToCylinderOverlap(Collider* possibleCollider, Vector3& collisionNormal)
{
	return false;
}

void Collider::PenetrationResolution(Vector3 collisionNormal, float distance)
{
	if (m_kinematic)
		return;

	m_position = m_position + collisionNormal * distance;
}

void Collider::OnCollisionStart(Collider* collider, Vector3 collisionNormal, bool isReply)
{
	//std::cout << "collision start" << std::endl;

	if (!isReply)
		collider->OnCollisionStart(this, -collisionNormal, true);

	if (m_kinematic || m_simulationFreeze)
		return;

	m_dragCoeficitient = m_friction;

	Vector3 relativeVelocity = m_velocity - collider->m_velocity;
	float vn = relativeVelocity.dot(collisionNormal);

	if (vn > 0)
		return;

	float numerator = -(1 + m_elasticity) * vn;
	float denominator = (1.0f / m_mass) + (1.0f / collider->m_mass);
	float impulseMagnitude = numerator / denominator;

	AddForce((collisionNormal * impulseMagnitude) / m_mass, ForceType::IMPULSE);
	collider->AddForce((-collisionNormal * impulseMagnitude) / collider->m_mass, ForceType::IMPULSE);
}

void Collider::OnCollisionEnd(Collider* collider, bool isReply)
{
	//std::cout << "collision end" << std::endl;

	if (!isReply)
		collider->OnCollisionEnd(this, true);

	if (m_kinematic || m_simulationFreeze)
		return;

	if (m_collisions.empty())
		m_dragCoeficitient = m_drag;
}

void Collider::OnCollisionStay(Collider* collider, Vector3 collisionNormal, bool isReply)
{
	//std::cout << "collision stay" << std::endl;

	if (!isReply)
		collider->OnCollisionStay(this, -collisionNormal, true);

	if (m_kinematic || m_simulationFreeze)
		return;
	
	if (collisionNormal.m_y == 1)
	{
		if (m_position.m_y > collider->m_position.m_y)
		{
			AddForce(collisionNormal * m_gravity * m_mass);
		}
	}
}

void Collider::PhysicsUpdate(float deltaTime)
{
	m_deltaTime = deltaTime;

	if (m_simulationFreeze)
		return;

	AddForce(Vector3(0, -m_gravity * m_mass, 0));
	AddForce(Vector3(m_velocity * m_mass * (-m_dragCoeficitient)));
	m_position = m_position + (m_velocity * deltaTime);
}

void Collider::AddForce(Vector3 force, ForceType type)
{
	if (m_kinematic)
		return;

	switch (type)
	{
		case ForceType::VELOCITY_CHANGE:
			m_velocity = force;
			break;
		case ForceType::IMPULSE:
			m_velocity = m_velocity + force;
			break;
		case ForceType::ACCELERATION:
			m_velocity = m_velocity + (force / m_mass) * m_deltaTime;
			break;
		default:
			break;
	}
}
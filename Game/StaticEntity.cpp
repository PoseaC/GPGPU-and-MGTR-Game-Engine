#include "StaticEntity.h"

StaticEntity::StaticEntity()
{
}

StaticEntity::~StaticEntity()
{
}

void StaticEntity::OnCreate()
{
	Entity::OnCreate();
	m_vertexPositions =
	{
		//front face
		Vector3(-5.0f, -0.5f, -5.0f),
		Vector3(-5.0f, 0.5f, -5.0f),
		Vector3(5.0f, 0.5f, -5.0f),
		Vector3(5.0f, -0.5f, -5.0f),

		//back face
		Vector3(5.0f, -0.5f, 5.0f),
		Vector3(5.0f, 0.5f, 5.0f),
		Vector3(-5.0f, 0.5f, 5.0f),
		Vector3(-5.0f, -0.5f, 5.0f),
	};
}

void StaticEntity::OnUpdate(float deltaTime)
{
	Entity::OnUpdate(deltaTime);
}

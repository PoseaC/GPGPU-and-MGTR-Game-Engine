#include <OpenGL/Entity/Entity.h>
#include <OpenGL/Entity/EntitySystem.h>

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::OnCreate()
{
	m_vertexPositions =
	{
		//front face
		Vector3(-0.5f, -0.5f, -0.5f),
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.5f, -0.5f, -0.5f),

		//back face
		Vector3(0.5f, -0.5f, 0.5f),
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, -0.5f, 0.5f),
	};

	m_indicesList =
	{
		//front
		0, 1, 2,
		2, 3, 0,

		//back
		4, 5, 6,
		6, 7, 4,

		//top
		8, 9, 10,
		10, 11, 8,

		//bottom
		12, 13, 14,
		14, 15, 12,

		//right
		16, 17, 18,
		18, 19, 16,

		//left
		20, 21, 22,
		22, 23, 20
	};

	m_textureCoords =
	{
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,0),
		Vector2(1,1),
	};

	m_vertices =
	{
		//front face
		{ m_vertexPositions[0], m_textureCoords[1] },
		{ m_vertexPositions[1], m_textureCoords[0] },
		{ m_vertexPositions[2], m_textureCoords[2] },
		{ m_vertexPositions[3], m_textureCoords[3] },

		//back face
		{ m_vertexPositions[4], m_textureCoords[1] },
		{ m_vertexPositions[5], m_textureCoords[0] },
		{ m_vertexPositions[6], m_textureCoords[2] },
		{ m_vertexPositions[7], m_textureCoords[3] },

		//top face
		{ m_vertexPositions[1], m_textureCoords[1] },
		{ m_vertexPositions[6], m_textureCoords[0] },
		{ m_vertexPositions[5], m_textureCoords[2] },
		{ m_vertexPositions[2], m_textureCoords[3] },

		//bottom face
		{ m_vertexPositions[7], m_textureCoords[1] },
		{ m_vertexPositions[0], m_textureCoords[0] },
		{ m_vertexPositions[3], m_textureCoords[2] },
		{ m_vertexPositions[4], m_textureCoords[3] },

		//right face
		{ m_vertexPositions[3], m_textureCoords[1] },
		{ m_vertexPositions[2], m_textureCoords[0] },
		{ m_vertexPositions[5], m_textureCoords[2] },
		{ m_vertexPositions[4], m_textureCoords[3] },

		//left face
		{ m_vertexPositions[7], m_textureCoords[1] },
		{ m_vertexPositions[6], m_textureCoords[0] },
		{ m_vertexPositions[1], m_textureCoords[2] },
		{ m_vertexPositions[0], m_textureCoords[3] },
	};

	m_vertexAttribs =
	{
		VertexAttribute(sizeof(Vector3) / sizeof(float)), //position
		VertexAttribute(sizeof(Vector2) / sizeof(float)) //texcoord
	};

	m_position = Vector3(0, 0, 0);
}

void Entity::OnUpdate(float deltaTime)
{
	Vector3 temp[] =
	{
		//front face
		Vector3(m_position.m_x + m_vertexPositions[0].m_x, m_position.m_y + m_vertexPositions[0].m_y, m_position.m_z + m_vertexPositions[0].m_z),
		Vector3(m_position.m_x + m_vertexPositions[1].m_x, m_position.m_y + m_vertexPositions[1].m_y, m_position.m_z + m_vertexPositions[1].m_z),
		Vector3(m_position.m_x + m_vertexPositions[2].m_x, m_position.m_y + m_vertexPositions[2].m_y, m_position.m_z + m_vertexPositions[2].m_z),
		Vector3(m_position.m_x + m_vertexPositions[3].m_x, m_position.m_y + m_vertexPositions[3].m_y, m_position.m_z + m_vertexPositions[3].m_z),

		//back face
		Vector3(m_position.m_x + m_vertexPositions[4].m_x, m_position.m_y + m_vertexPositions[4].m_y, m_position.m_z + m_vertexPositions[4].m_z),
		Vector3(m_position.m_x + m_vertexPositions[5].m_x, m_position.m_y + m_vertexPositions[5].m_y, m_position.m_z + m_vertexPositions[5].m_z),
		Vector3(m_position.m_x + m_vertexPositions[6].m_x, m_position.m_y + m_vertexPositions[6].m_y, m_position.m_z + m_vertexPositions[6].m_z),
		Vector3(m_position.m_x + m_vertexPositions[7].m_x, m_position.m_y + m_vertexPositions[7].m_y, m_position.m_z + m_vertexPositions[7].m_z),
	};

	m_vertices =
	{
		//front face
		{ temp[0], m_textureCoords[1] },
		{ temp[1], m_textureCoords[0] },
		{ temp[2], m_textureCoords[2] },
		{ temp[3], m_textureCoords[3] },

		//back face
		{ temp[4], m_textureCoords[1] },
		{ temp[5], m_textureCoords[0] },
		{ temp[6], m_textureCoords[2] },
		{ temp[7], m_textureCoords[3] },

		//top face
		{ temp[1], m_textureCoords[1] },
		{ temp[6], m_textureCoords[0] },
		{ temp[5], m_textureCoords[2] },
		{ temp[2], m_textureCoords[3] },

		//bottom face
		{ temp[7], m_textureCoords[1] },
		{ temp[0], m_textureCoords[0] },
		{ temp[3], m_textureCoords[2] },
		{ temp[4], m_textureCoords[3] },

		//right face
		{ temp[3], m_textureCoords[1] },
		{ temp[2], m_textureCoords[0] },
		{ temp[5], m_textureCoords[2] },
		{ temp[4], m_textureCoords[3] },

		//left face
		{ temp[7], m_textureCoords[1] },
		{ temp[6], m_textureCoords[0] },
		{ temp[1], m_textureCoords[2] },
		{ temp[0], m_textureCoords[3] },
	};
}

void Entity::CheckOverlap(Entity* possibleCollider)
{
	float epsilon = 0.0001f;
	Vector3& thisTopRightFront = m_vertices[2].position;
	Vector3& thisBottomLeftBack = m_vertices[7].position;

	Vector3& colliderTopRightFront = possibleCollider->m_vertices[2].position;
	Vector3& colliderBottomLeftBack = possibleCollider->m_vertices[7].position;

	bool isOverlapping = (thisTopRightFront.m_x > colliderBottomLeftBack.m_x - epsilon && thisTopRightFront.m_y > colliderBottomLeftBack.m_y - epsilon && thisTopRightFront.m_z < colliderBottomLeftBack.m_z + epsilon) &&
						(thisBottomLeftBack.m_x < colliderTopRightFront.m_x + epsilon && thisBottomLeftBack.m_y < colliderTopRightFront.m_y + epsilon && thisBottomLeftBack.m_z > colliderTopRightFront.m_z - epsilon);

	if (isOverlapping)
	{
		if (m_collisions.find(possibleCollider) != m_collisions.end())
		{
			OnCollisionStay(possibleCollider);
		}
		else
		{
			OnCollisionStart(possibleCollider);
			m_collisions.emplace(possibleCollider);
		}
	}
	else if (m_collisions.find(possibleCollider) != m_collisions.end())
	{
		OnCollisionEnd(possibleCollider);
		m_collisions.erase(possibleCollider);
	}
}

void Entity::release()
{
	m_entitySystem->removeEntity(this);
}

EntitySystem* Entity::getEntitySystem()
{
	return m_entitySystem;
}

void Entity::setPosition(Vector3 newPosition)
{
	m_position = newPosition;
}

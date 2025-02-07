#include <OpenGL/Entity/Entity.h>
#include <OpenGL/Entity/EntitySystem.h>
#include <OpenGL/Graphics/GraphicsEngine.h>

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

	m_vertexNormals =
	{
		//back face 
		Vector3(0, 0, -1),

		//front face
		Vector3(0, 0, 1),

		//top face
		Vector3(0, 1, 0),

		//bottom face
		Vector3(0, -1, 0),

		//left face
		Vector3(-1, 0, 0),

		//right face
		Vector3(1, 0, 0)
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
		{ m_vertexPositions[0], m_textureCoords[1], m_vertexNormals[0] },
		{ m_vertexPositions[1], m_textureCoords[0], m_vertexNormals[0] },
		{ m_vertexPositions[2], m_textureCoords[2], m_vertexNormals[0] },
		{ m_vertexPositions[3], m_textureCoords[3], m_vertexNormals[0] },

		//back face
		{ m_vertexPositions[4], m_textureCoords[1], m_vertexNormals[1] },
		{ m_vertexPositions[5], m_textureCoords[0], m_vertexNormals[1] },
		{ m_vertexPositions[6], m_textureCoords[2], m_vertexNormals[1] },
		{ m_vertexPositions[7], m_textureCoords[3], m_vertexNormals[1] },

		//top face
		{ m_vertexPositions[1], m_textureCoords[1], m_vertexNormals[2] },
		{ m_vertexPositions[6], m_textureCoords[0], m_vertexNormals[2] },
		{ m_vertexPositions[5], m_textureCoords[2], m_vertexNormals[2] },
		{ m_vertexPositions[2], m_textureCoords[3], m_vertexNormals[2] },

		//bottom face
		{ m_vertexPositions[7], m_textureCoords[1], m_vertexNormals[3] },
		{ m_vertexPositions[0], m_textureCoords[0], m_vertexNormals[3] },
		{ m_vertexPositions[3], m_textureCoords[2], m_vertexNormals[3] },
		{ m_vertexPositions[4], m_textureCoords[3], m_vertexNormals[3] },

		//right face
		{ m_vertexPositions[3], m_textureCoords[1], m_vertexNormals[4] },
		{ m_vertexPositions[2], m_textureCoords[0], m_vertexNormals[4] },
		{ m_vertexPositions[5], m_textureCoords[2], m_vertexNormals[4] },
		{ m_vertexPositions[4], m_textureCoords[3], m_vertexNormals[4] },

		//left face
		{ m_vertexPositions[7], m_textureCoords[1], m_vertexNormals[4] },
		{ m_vertexPositions[6], m_textureCoords[0], m_vertexNormals[4] },
		{ m_vertexPositions[1], m_textureCoords[2], m_vertexNormals[4] },
		{ m_vertexPositions[0], m_textureCoords[3], m_vertexNormals[4] },
	};

	m_vertexAttribs =
	{
		VertexAttribute(sizeof(Vector3) / sizeof(float)), // position
		VertexAttribute(sizeof(Vector2) / sizeof(float)), // texture coord
		VertexAttribute(sizeof(Vector3) / sizeof(float)) // normal
	};

	m_transform.setIdentity();
	m_position = Vector3(0, 0, 0);
	m_shininess = 30;
	boundingBoxCornerOffset = Vector3(0.5, 0.5, -0.5);
	m_texture = std::make_unique<Texture>("Assets/Textures/checkerboard.jpg");
	m_color = Vector3(1, 0, 0);
}

void Entity::OnUpdate(float deltaTime)
{
	m_transform.setTranslation(m_position);
}

void Entity::CheckOverlap(Entity* possibleCollider)
{
	float epsilon = 0.0001f;
	Vector3 thisTopRightFront = m_position + boundingBoxCornerOffset;
	Vector3 thisBottomLeftBack = m_position - boundingBoxCornerOffset;

	Vector3 colliderTopRightFront = possibleCollider->m_position + possibleCollider->boundingBoxCornerOffset;
	Vector3 colliderBottomLeftBack = possibleCollider->m_position - possibleCollider->boundingBoxCornerOffset;

	bool isOverlapping = (thisTopRightFront.m_x > colliderBottomLeftBack.m_x - epsilon && thisTopRightFront.m_y > colliderBottomLeftBack.m_y - epsilon && thisTopRightFront.m_z < colliderBottomLeftBack.m_z + epsilon) &&
						(thisBottomLeftBack.m_x < colliderTopRightFront.m_x + epsilon && thisBottomLeftBack.m_y < colliderTopRightFront.m_y + epsilon && thisBottomLeftBack.m_z > colliderTopRightFront.m_z - epsilon);

	if (isOverlapping)
	{
		float overlapX = fminf(thisTopRightFront.m_x, colliderTopRightFront.m_x) - fmaxf(thisBottomLeftBack.m_x, colliderBottomLeftBack.m_x);
		float overlapY = fminf(thisTopRightFront.m_y, colliderTopRightFront.m_y) - fmaxf(thisBottomLeftBack.m_y, colliderBottomLeftBack.m_y);
		float overlapZ = fminf(thisTopRightFront.m_z, colliderTopRightFront.m_z) - fmaxf(thisBottomLeftBack.m_z, colliderBottomLeftBack.m_z);

		Vector3 collisionNormal;

		if (overlapX < overlapY)
		{
			if (overlapX < overlapZ)
				collisionNormal = Vector3(1, 0, 0);
			else
				collisionNormal = Vector3(0, 0, 1);
		}
		else
			collisionNormal = Vector3(0, 1, 0);

		if (m_collisions.find(possibleCollider) != m_collisions.end())
		{
			OnCollisionStay(possibleCollider, collisionNormal);
		}
		else
		{
			OnCollisionStart(possibleCollider, collisionNormal);
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

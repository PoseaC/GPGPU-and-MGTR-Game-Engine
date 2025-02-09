#include <OpenGL/Entity/EntitySystem.h>
#include <OpenGL/Entity/Entity.h>

EntitySystem::EntitySystem()
{
	m_colliderComputeShader = ShaderProgram::CreateComputeShader("Assets/Shaders/ColliderComputeShader.glsl");
}

EntitySystem::~EntitySystem()
{
}

bool EntitySystem::registerEntity(Entity* entity)
{
	m_entities.emplace(entity);

	entity->m_entitySystem = this;
	entity->OnCreate();

	return true;
}

void EntitySystem::removeEntity(Entity* entity)
{
	m_entitiesToDestroy.emplace(entity);
}

void EntitySystem::update(float deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities.erase(e);
	}
	m_entitiesToDestroy.clear();

	for (auto& entity : m_entities)
	{
		entity->m_simulationFreeze = m_simulationFreeze;
		entity->OnUpdate(deltaTime);
	}

	collisionDetectionCPU();
}

void EntitySystem::collisionDetectionCPU()
{
	for (auto it1 = m_entities.begin(); it1 != m_entities.end(); it1++)
	{
		for (auto it2 = it1; it2 != m_entities.end(); it2++)
		{
			if (it1 != it2)
				(*it1)->CheckOverlap(*it2);
		}
	}
}

void EntitySystem::collisionDetectionGPU()
{
	std::vector<ColliderDataBuffer> colliderData;
	colliderData.reserve(m_entities.size());
	for (const auto& entity : m_entities)
	{
		ColliderDataBuffer data;

		data.position = entity->m_position;
		data.velocity = entity->m_velocity;
		data.boxSize = entity->m_boxSize;
		data.mass = entity->m_mass;
		data.isKinematic = entity->m_kinematic;
		data.isTrigger = entity->m_trigger;
		data.elasticity = entity->m_elasticity;
		data.friction = entity->m_friction;
		data.drag = entity->m_drag;
		data.deltaTime = entity->m_deltaTime;

		colliderData.push_back(data);
	}

	GLuint colliderSSBO;
	glGenBuffers(1, &colliderSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colliderSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, colliderData.size() * sizeof(ColliderDataBuffer), colliderData.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, colliderSSBO);

	glUseProgram(m_colliderComputeShader);
	glDispatchCompute((GLuint)(m_entities.size() / 256 + 1), 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	ColliderDataBuffer* computedColliderData = (ColliderDataBuffer*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	int index = 0;
	for (const auto& entity : m_entities)
	{
		ColliderDataBuffer& data = computedColliderData[index];

		entity->m_position = data.position;
		entity->m_velocity = data.velocity;

		index++;
	}
}

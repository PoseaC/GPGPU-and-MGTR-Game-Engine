#include <OpenGL/Graphics/VertexArrayObject.h>
#include <Prerequisites.h>
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& data)
{
	if (!data.listSize)
		GL_ERROR("VertexArrayObject | listSize is NULL");
	
	if (!data.vertexSize)
		GL_ERROR("VertexArrayObject | vertexSize is NULL");
	
	if (!data.verticesList)
		GL_ERROR("VertexArrayObject | verticesList is NULL");

	glGenVertexArrays(1, &m_vertexArrayObjectId);
	glBindVertexArray(m_vertexArrayObjectId);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	for (unsigned int i = 0; i < data.attributeListSize; i++)
	{
		glVertexAttribPointer(
			i,
			data.attributeList[i].numElements,
			GL_FLOAT,
			GL_FALSE,
			data.vertexSize,
			(void*) ((i==0) ? 0 : data.attributeList[i - 1].numElements * sizeof(float))
		);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

unsigned int VertexArrayObject::getId()
{
	return m_vertexArrayObjectId;
}

unsigned int VertexArrayObject::getVertexBufferSize()
{
	return m_vertexBufferData.listSize;
}

unsigned int VertexArrayObject::getVertexSize()
{
	return m_vertexBufferData.vertexSize;
}

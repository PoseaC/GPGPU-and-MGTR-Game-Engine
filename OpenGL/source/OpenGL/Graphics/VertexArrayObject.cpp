#include <OpenGL/Graphics/VertexArrayObject.h>
#include <Prerequisites.h>
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const VertexBufferData& data)
{
	glGenBuffers(1, &m_vertexBufferId);

	glGenVertexArrays(1, &m_vertexArrayObjectId);
	glBindVertexArray(m_vertexArrayObjectId);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	glEnableVertexAttribArray(0);

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

#include <OpenGL/Graphics/VertexArrayObject.h>
#include <Prerequisites.h>
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc)
{
	if (!vbDesc.listSize)
		GL_ERROR("VertexArrayObject | listSize is NULL");
	
	if (!vbDesc.vertexSize)
		GL_ERROR("VertexArrayObject | vertexSize is NULL");
	
	if (!vbDesc.verticesList)
		GL_ERROR("VertexArrayObject | verticesList is NULL");

	glGenVertexArrays(1, &m_vertexArrayObjectId);
	glBindVertexArray(m_vertexArrayObjectId);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vbDesc.vertexSize * vbDesc.listSize, vbDesc.verticesList, GL_STATIC_DRAW);

	for (unsigned int i = 0; i < vbDesc.attributeListSize; i++)
	{
		glVertexAttribPointer(
			i,
			vbDesc.attributeList[i].numElements,
			GL_FLOAT,
			GL_FALSE,
			vbDesc.vertexSize,
			(void*) ((i==0) ? 0 : vbDesc.attributeList[i - 1].numElements * sizeof(float))
		);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = vbDesc;
}

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc) : VertexArrayObject(vbDesc)
{
	if (!ibDesc.listSize)
		GL_ERROR("VertexArrayObject | listSize is NULL");

	if (!ibDesc.indicesList)
		GL_ERROR("VertexArrayObject | indicesList is NULL");

	glBindVertexArray(m_vertexArrayObjectId);

	glGenBuffers(1, &m_elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_elementBufferId);
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

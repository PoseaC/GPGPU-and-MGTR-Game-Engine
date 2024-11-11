#pragma once
#include <OpenGL/Math/Vector4.h>
#include <Prerequisites.h>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& vbDesc);
	VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	~VertexArrayObject();

	unsigned int getId();
	unsigned int getVertexBufferSize();
	unsigned int getVertexSize();

private:
	unsigned int m_vertexBufferId = 0;
	unsigned int m_elementBufferId = 0;
	unsigned int m_vertexArrayObjectId = 0;
	VertexBufferDesc m_vertexBufferData;
};

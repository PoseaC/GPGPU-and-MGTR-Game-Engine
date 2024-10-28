#pragma once
#include <OpenGL/Math/Vector4.h>
#include <Prerequisites.h>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferData& data);
	~VertexArrayObject();

	unsigned int getId();
	unsigned int getVertexBufferSize();
	unsigned int getVertexSize();

private:
	unsigned int m_vertexBufferId = 0;
	unsigned int m_vertexArrayObjectId = 0;
	VertexBufferData m_vertexBufferData;
};

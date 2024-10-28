#pragma once
#include <memory>

class VertexArrayObject;
typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;

struct VertexBufferData
{
	void* verticesList = nullptr;
	int vertexSize = 0;
	int listSize = 0;
};
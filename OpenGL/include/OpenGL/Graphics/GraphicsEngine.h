#pragma once
#include <OpenGL/Math/Vector4.h>
#include <OpenGL/Math/Rect.h>
#include <Prerequisites.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& data);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);

	void Clear(const Vector4& color);
	void SetViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setShaderProgram(const ShaderProgramPtr& program);
	void drawTriangles(int vertexCount, int offset);
};


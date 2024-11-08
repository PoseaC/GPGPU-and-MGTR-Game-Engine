#pragma once
#include <OpenGL/Math/Vector4.h>
#include <OpenGL/Math/Rect.h>
#include <Prerequisites.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& desc);
	UniformBufferPtr createUniformBuffer(const UniformBufferDesc& desc);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);

	void Clear(const Vector4& color);
	void SetViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setUniformBuffer(const UniformBufferPtr& buffer, unsigned int slot);
	void setShaderProgram(const ShaderProgramPtr& program);
	void drawTriangles(const TriangleType& triangleType, int vertexCount, int offset);
};


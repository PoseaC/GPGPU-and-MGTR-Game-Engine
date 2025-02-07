#pragma once
#include <OpenGL/Math/Vector4.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Rect.h>
#include <Prerequisites.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc);
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	UniformBufferPtr createUniformBuffer(const UniformBufferDesc& desc);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);

	void Clear(const Vector4& color);
	void setFaceCulling(const CullType& type);
	void setWindingOrder(const WindingOrder& type);
	void setViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setUniformBuffer(const UniformBufferPtr& buffer, unsigned int slot);
	void setShaderProgram(const ShaderProgramPtr& program);
	void drawTriangles(const TriangleType& triangleType, int vertexCount, int offset);
	void drawIndexedTriangles(const TriangleType& triangleType, int indicesCount);
	void setPointLights(const ShaderProgramPtr& shader, const int count, const Vector3* positions, const Vector3* colors);
	void setEyePosition(const ShaderProgramPtr& shader, const Vector3 eyePosition);
	void setMaterialAttributes(const ShaderProgramPtr& shader, const Vector3& color, const int& shininess);
	void CheckGLError(const char* context);
};


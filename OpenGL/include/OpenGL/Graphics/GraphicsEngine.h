#pragma once
#include <OpenGL/Math/Vector4.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Rect.h>
#include <Prerequisites.h>
#include <OpenGL/Entity/Entity.h>
#include <set>

struct UniformData
{
	Mat4 model;
	Mat4 view;
	Mat4 projection;
};

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
	void setPointLights(const ShaderProgramPtr& shader, const int count, float* positions, float* colors);
	void setEyePosition(const Vector3 eyePosition);
	void CheckGLError(const char* context);
	void drawEntities(const std::set<Entity*> entities, const int pointLightCount, float* pointLightPositions, float* pointLightColors, const Rect display);
	void setViewMatrix(Mat4 view);

	UniformBufferPtr m_uniform;
	Mat4 m_projection;
	Mat4 m_view;

private:
	Vector3 m_eyePosition;
	void setEyePosition(const ShaderProgramPtr& shader, const Vector3 eyePosition);
};


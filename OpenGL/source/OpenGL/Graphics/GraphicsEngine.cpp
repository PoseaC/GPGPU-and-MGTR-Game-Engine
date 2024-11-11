#include <OpenGL/Graphics/GraphicsEngine.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/UniformBuffer.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc)
{
	return std::make_shared<VertexArrayObject>(vbDesc);
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
{
	return std::make_shared<VertexArrayObject>(vbDesc, ibDesc);
}

UniformBufferPtr GraphicsEngine::createUniformBuffer(const UniformBufferDesc& desc)
{
	return std::make_shared<UniformBuffer>(desc);
}

ShaderProgramPtr GraphicsEngine::createShaderProgram(const ShaderProgramDesc& desc)
{
	return std::make_shared<ShaderProgram>(desc);
}

void GraphicsEngine::Clear(const Vector4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::setFaceCulling(const CullType& type)
{
	auto cullType = GL_BACK;

	if (type == CullType::BackFace)
		cullType = GL_BACK;
	else if (type == CullType::FrontFace)
		cullType = GL_FRONT;
	else if (type == CullType::Both)
		cullType = GL_FRONT_AND_BACK;

	glEnable(GL_CULL_FACE);
	glCullFace(cullType);
}

void GraphicsEngine::setWindingOrder(const WindingOrder& type)
{
	auto orderType = GL_CW;

	if (type == WindingOrder::Clockwise)
		orderType = GL_CW;
	else if (type == WindingOrder::AntiClockwise)
		orderType = GL_CCW;

	glFrontFace(orderType);
}

void GraphicsEngine::setViewport(const Rect& size)
{
	glViewport(size.left, size.top, size.width, size.height);
}

void GraphicsEngine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getId());
}

void GraphicsEngine::setUniformBuffer(const UniformBufferPtr& buffer, unsigned int slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

void GraphicsEngine::setShaderProgram(const ShaderProgramPtr& program)
{
	glUseProgram(program->getId());
}

void GraphicsEngine::drawTriangles(const TriangleType& triangleType, int vertexCount, int offset)
{
	auto glTriangleType = GL_TRIANGLES;

	switch (triangleType)
	{
		case TriangleType::TriangleList:
			glTriangleType = GL_TRIANGLES;
			break;

		case TriangleType::TriangleStrip:
			glTriangleType = GL_TRIANGLE_STRIP;
			break;
	}

	glDrawArrays(glTriangleType, offset, vertexCount);
}

void GraphicsEngine::drawIndexedTriangles(const TriangleType& triangleType, int indicesCount)
{
	auto glTriangleType = GL_TRIANGLES;

	switch (triangleType)
	{
		case TriangleType::TriangleList:
			glTriangleType = GL_TRIANGLES;
			break;

		case TriangleType::TriangleStrip:
			glTriangleType = GL_TRIANGLE_STRIP;
			break;
	}

	glDrawElements(glTriangleType, indicesCount, GL_UNSIGNED_INT, nullptr);
}

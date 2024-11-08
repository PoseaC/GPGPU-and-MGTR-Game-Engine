#include <OpenGL/Graphics/GraphicsEngine.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/UniformBuffer.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& desc)
{
	return std::make_shared<VertexArrayObject>(desc);
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

void GraphicsEngine::SetViewport(const Rect& size)
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
		case TriangleList:
			glTriangleType = GL_TRIANGLES;
			break;

		case TriangleStrip:
			glTriangleType = GL_TRIANGLE_STRIP;
			break;
	}

	glDrawArrays(glTriangleType, offset, vertexCount);
}

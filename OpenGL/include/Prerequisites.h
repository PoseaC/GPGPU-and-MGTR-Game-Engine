#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

class VertexArrayObject;
class UniformBuffer;
class ShaderProgram;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

struct VertexAttribute
{
	unsigned int numElements = 0;
};

struct VertexBufferDesc
{
	void* verticesList = nullptr;
	unsigned int vertexSize = 0;
	unsigned int listSize = 0;

	VertexAttribute* attributeList = nullptr;
	unsigned int attributeListSize = 0;
};

struct ShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

struct UniformBufferDesc
{
	unsigned int size = 0;
};

enum TriangleType
{
	TriangleList = 0,
	TriangleStrip
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader
};

#define GL_ERROR(message)\
{\
	std::stringstream m;\
	m << "Error: " << message << std::endl;\
	throw std::runtime_error(m.str());\
}

#define GL_WARNING(message)\
std::cout << "Warning: " << message << std::endl;

#define GL_INFO(message)\
std::cout << "Info: " << message << std::endl;
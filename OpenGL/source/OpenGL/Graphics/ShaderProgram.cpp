#include <OpenGL/Graphics/ShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFilePath, VertexShader);
	attach(desc.fragmentShaderFilePath, FragmentShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	for (int i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programId);
}

unsigned int ShaderProgram::getId()
{
	return m_programId;
}

void ShaderProgram::setUniformBufferSlot(const char* name, unsigned int slot)
{
	unsigned int index = glGetUniformBlockIndex(m_programId, name);
	glUniformBlockBinding(m_programId, index, slot);
}

void ShaderProgram::attach(const wchar_t* shaderFilePath, const ShaderType& type)
{
	std::wstring ws(shaderFilePath);
	std::string str(ws.begin(), ws.end());

	auto p = std::filesystem::path(shaderFilePath);
	std::ifstream shaderStream(p);

	if (!shaderStream.is_open())
		GL_ERROR(std::format("ShaderProgram | {} not found", str));

	std::string shaderCode;
	std::stringstream sstr;

	sstr << shaderStream.rdbuf();
	shaderCode = sstr.str();
	shaderStream.close();

	unsigned int shaderId = 0;
	if (type == VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	int logLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
		GL_ERROR(std::format("ShaderProgram | {} compiled with errors: \n{}", str, &errorMessage[0]));
	}

	glAttachShader(m_programId, shaderId);
	m_attachedShaders[type] = shaderId;

	GL_INFO(std::format("ShaderProgram | {} compiled successfully", str));
}

void ShaderProgram::link()
{
	glLinkProgram(m_programId);

	int logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
		GL_ERROR(std::format("ShaderProgram | {}", &errorMessage[0]));
	}
}

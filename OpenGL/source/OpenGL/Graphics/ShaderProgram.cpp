#include <OpenGL/Graphics/ShaderProgram.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFilePath, ShaderType::VertexShader);
	attach(desc.fragmentShaderFilePath, ShaderType::FragmentShader);
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
	if (type == ShaderType::VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderType::FragmentShader)
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
	m_attachedShaders[(int) type] = shaderId;

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

void ShaderProgram::setUniform(const std::string& name, int value) {
	int location = glGetUniformLocation(m_programId, name.c_str());
	glUniform1i(location, value);
	if (location == -1) std::cerr << "Uniform not found!" << std::endl;
}

GLuint ShaderProgram::CreateComputeShader(const std::string filepath) {
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		GL_ERROR(std::format("Failed to load shader file | {}", filepath));
	}

	std::stringstream shaderStream;
	shaderStream << file.rdbuf();
	const GLchar* shaderSource = shaderStream.str().c_str();
	GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		GL_ERROR(std::format("Compute Shader Compilation Failed | {}", infoLog));
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		GL_ERROR(std::format("Compute Shader Linking Failed | {}", infoLog));
	}

	glDeleteShader(shader);
	return program;
}

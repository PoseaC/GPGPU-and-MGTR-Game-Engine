#pragma once
#include <Prerequisites.h>
#include <glad/glad.h>

class ShaderProgram
{
public:
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();
	unsigned int getId();
	void setUniformBufferSlot(const char* name, unsigned int slot);
	void setUniform(const std::string& name, int value);
	static GLuint CreateComputeShader(const std::string filepath);

private:
	void attach(const wchar_t* shaderFilePath, const ShaderType& type);
	void link();

	unsigned int m_programId = 0;
	unsigned int m_attachedShaders[2] = {};
};


#pragma once
#include <Prerequisites.h>

class ShaderProgram
{
public:
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();
	unsigned int getId();

private:
	void attach(const wchar_t* shaderFilePath, const ShaderType& type);
	void link();

	unsigned int m_programId = 0;
	unsigned int m_attachedShaders[2] = {};
};


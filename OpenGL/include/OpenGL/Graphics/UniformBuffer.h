#pragma once
#include <Prerequisites.h>

class UniformBuffer
{
public:
	UniformBuffer(const UniformBufferDesc& desc);
	~UniformBuffer();

	void setData(void* data);

	unsigned int getId();
private:
	unsigned int m_id = 0;
	unsigned int m_size = 0;
};


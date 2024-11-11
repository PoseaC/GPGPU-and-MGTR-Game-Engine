#version 410 core

layout (row_major) uniform UniformData
{
	mat4 world;
	mat4 projection;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;

layout (location = 0) out vec3 outColor;

void main()
{
	gl_Position = vec4(position, 1) * world * projection;
	outColor = vec3(texcoord.x, texcoord.y, 0);
}
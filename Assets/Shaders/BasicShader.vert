#version 410 core

uniform UniformData
{
	mat4 model;
	mat4 view;
	mat4 projection;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 normal;

out vec2 tex_coord;
out vec3 world_position;
out vec3 world_normal;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1);
    tex_coord = texcoord;
	world_position = (model * vec4(position, 1.0)).xyz;
	world_normal = normalize(mat3(transpose(inverse(model))) * normal);
}
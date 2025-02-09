#pragma once
#include <Prerequisites.h>
#include <vector>
#include <OpenGL/Math/Mat4.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Vector2.h>
#include <OpenGL/Graphics/Texture.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>

struct Vertex
{
	Vector3 position;
	Vector2 texcoord;
	Vector3 normal;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void prepareMesh();

	VertexArrayObjectPtr m_polygonVAO = nullptr;
	std::vector<Vector3> m_vertexPositions;
	std::vector<Vector3> m_vertexNormals;
	std::vector<VertexAttribute> m_vertexAttribs;
	std::vector<unsigned int> m_indicesList;
	std::vector<Vertex> m_vertices;

	std::unique_ptr<Texture> m_texture;
	std::vector <Vector2> m_textureCoords;
	Vector3 m_color;
	int m_shininess;
	ShaderProgramPtr m_shader = nullptr;
	ShaderProgramDesc m_shaderDesc;

private:
	void setMaterialAttributes();
};


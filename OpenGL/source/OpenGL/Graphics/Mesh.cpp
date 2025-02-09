#include <OpenGL/Graphics/Mesh.h>

Mesh::Mesh()
{
	m_vertexPositions =
	{
		//front face
		Vector3(-1, -1, -1),
		Vector3(-1, 1, -1),
		Vector3(1, 1, -1),
		Vector3(1, -1, -1),

		//back face
		Vector3(1, -1, 1),
		Vector3(1, 1, 1),
		Vector3(-1, 1, 1),
		Vector3(-1, -1, 1),
	};

	m_vertexNormals =
	{
		//back face 
		Vector3(0, 0, -1),

		//front face
		Vector3(0, 0, 1),

		//top face
		Vector3(0, 1, 0),

		//bottom face
		Vector3(0, -1, 0),

		//left face
		Vector3(-1, 0, 0),

		//right face
		Vector3(1, 0, 0)
	};

	m_indicesList =
	{
		//front
		0, 1, 2,
		2, 3, 0,

		//back
		4, 5, 6,
		6, 7, 4,

		//top
		8, 9, 10,
		10, 11, 8,

		//bottom
		12, 13, 14,
		14, 15, 12,

		//right
		16, 17, 18,
		18, 19, 16,

		//left
		20, 21, 22,
		22, 23, 20
	};

	m_textureCoords =
	{
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,0),
		Vector2(1,1),
	};

	m_vertices =
	{
		//front face
		{ m_vertexPositions[0], m_textureCoords[1], m_vertexNormals[0] },
		{ m_vertexPositions[1], m_textureCoords[0], m_vertexNormals[0] },
		{ m_vertexPositions[2], m_textureCoords[2], m_vertexNormals[0] },
		{ m_vertexPositions[3], m_textureCoords[3], m_vertexNormals[0] },

		//back face
		{ m_vertexPositions[4], m_textureCoords[1], m_vertexNormals[1] },
		{ m_vertexPositions[5], m_textureCoords[0], m_vertexNormals[1] },
		{ m_vertexPositions[6], m_textureCoords[2], m_vertexNormals[1] },
		{ m_vertexPositions[7], m_textureCoords[3], m_vertexNormals[1] },

		//top face
		{ m_vertexPositions[1], m_textureCoords[1], m_vertexNormals[2] },
		{ m_vertexPositions[6], m_textureCoords[0], m_vertexNormals[2] },
		{ m_vertexPositions[5], m_textureCoords[2], m_vertexNormals[2] },
		{ m_vertexPositions[2], m_textureCoords[3], m_vertexNormals[2] },

		//bottom face
		{ m_vertexPositions[7], m_textureCoords[1], m_vertexNormals[3] },
		{ m_vertexPositions[0], m_textureCoords[0], m_vertexNormals[3] },
		{ m_vertexPositions[3], m_textureCoords[2], m_vertexNormals[3] },
		{ m_vertexPositions[4], m_textureCoords[3], m_vertexNormals[3] },

		//right face
		{ m_vertexPositions[3], m_textureCoords[1], m_vertexNormals[4] },
		{ m_vertexPositions[2], m_textureCoords[0], m_vertexNormals[4] },
		{ m_vertexPositions[5], m_textureCoords[2], m_vertexNormals[4] },
		{ m_vertexPositions[4], m_textureCoords[3], m_vertexNormals[4] },

		//left face
		{ m_vertexPositions[7], m_textureCoords[1], m_vertexNormals[4] },
		{ m_vertexPositions[6], m_textureCoords[0], m_vertexNormals[4] },
		{ m_vertexPositions[1], m_textureCoords[2], m_vertexNormals[4] },
		{ m_vertexPositions[0], m_textureCoords[3], m_vertexNormals[4] },
	};

	m_vertexAttribs =
	{
		VertexAttribute(sizeof(Vector3) / sizeof(float)), // position
		VertexAttribute(sizeof(Vector2) / sizeof(float)), // texture coord
		VertexAttribute(sizeof(Vector3) / sizeof(float)) // normal
	};

	m_shininess = 30;
	m_texture = std::make_unique<Texture>("Assets/Textures/checkerboard.jpg");
	m_color = Vector3(1, 0, 0);
	m_shaderDesc = {
		L"Assets/Shaders/BasicShader.vert",
		L"Assets/Shaders/BasicShader.frag"
	};
}

Mesh::~Mesh()
{
}

void Mesh::prepareMesh()
{
	m_texture->bind(0);
	m_shader->setUniform("u_texture", 0);
	setMaterialAttributes();
}

void Mesh::setMaterialAttributes()
{
	int location = glGetUniformLocation(m_shader->getId(), "material_ka");
	glUniform3fv(location, 1, &m_color.m_x);
	if (location == -1) std::cerr << "Uniform 'ka' not found!" << std::endl;

	location = glGetUniformLocation(m_shader->getId(), "material_kd");
	glUniform3fv(location, 1, &m_color.m_x);
	if (location == -1) std::cerr << "Uniform 'kd' not found!" << std::endl;

	location = glGetUniformLocation(m_shader->getId(), "material_ks");
	glUniform3fv(location, 1, &m_color.m_x);
	if (location == -1) std::cerr << "Uniform 'ks' not found!" << std::endl;

	location = glGetUniformLocation(m_shader->getId(), "material_shininess");
	glUniform1i(location, m_shininess);
	if (location == -1) std::cerr << "Uniform 'shiny' not found!" << std::endl;
}

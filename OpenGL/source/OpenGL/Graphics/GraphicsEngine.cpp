#include <OpenGL/Graphics/GraphicsEngine.h>
#include <OpenGL/Graphics/VertexArrayObject.h>
#include <OpenGL/Graphics/UniformBuffer.h>
#include <OpenGL/Graphics/ShaderProgram.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>

GraphicsEngine::GraphicsEngine()
{
	WNDCLASSEX window = {};
	window.cbSize = sizeof(WNDCLASSEX);
	window.lpszClassName = L"DummyWindow";
	window.lpfnWndProc = DefWindowProc;
	window.style = CS_OWNDC;

	auto classId = RegisterClassEx(&window);
	assert(classId);

	auto dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classId), L"GPGPU and MGTR Game Engine", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

	assert(dummyWindow);

	auto dummyDC = GetDC(dummyWindow); //DC = device context

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDesc.cColorBits = 32;
	pixelFormatDesc.cAlphaBits = 8;
	pixelFormatDesc.cDepthBits = 24;
	pixelFormatDesc.cStencilBits = 8;
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

	auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
	SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

	auto dummyContext = wglCreateContext(dummyDC);
	assert(dummyContext);

	bool res = wglMakeCurrent(dummyDC, dummyContext);
	assert(res);

	if (!gladLoadWGL(dummyDC))
		GL_ERROR("Graphics Engine Error - gladLoadWGL failed");

	if (!gladLoadGL())
		GL_ERROR("Graphics Engine Error - gladLoadGL failed");

	wglMakeCurrent(dummyDC, 0);
	wglDeleteContext(dummyContext);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);
}

GraphicsEngine::~GraphicsEngine()
{
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc)
{
	return std::make_shared<VertexArrayObject>(vbDesc);
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
{
	return std::make_shared<VertexArrayObject>(vbDesc, ibDesc);
}

UniformBufferPtr GraphicsEngine::createUniformBuffer(const UniformBufferDesc& desc)
{
	return std::make_shared<UniformBuffer>(desc);
}

ShaderProgramPtr GraphicsEngine::createShaderProgram(const ShaderProgramDesc& desc)
{
	CheckGLError("ShaderProgram Creation");
	return std::make_shared<ShaderProgram>(desc);
}

void GraphicsEngine::Clear(const Vector4& color)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(color.m_x, color.m_y, color.m_z, color.m_w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::setFaceCulling(const CullType& type)
{
	auto cullType = GL_BACK;

	if (type == CullType::BackFace)
		cullType = GL_BACK;
	else if (type == CullType::FrontFace)
		cullType = GL_FRONT;
	else if (type == CullType::Both)
		cullType = GL_FRONT_AND_BACK;

	glEnable(GL_CULL_FACE);
	glCullFace(cullType);
}

void GraphicsEngine::setWindingOrder(const WindingOrder& type)
{
	auto orderType = GL_CW;

	if (type == WindingOrder::Clockwise)
		orderType = GL_CW;
	else if (type == WindingOrder::AntiClockwise)
		orderType = GL_CCW;

	glFrontFace(orderType);
}

void GraphicsEngine::setViewport(const Rect& size)
{
	glViewport(size.left, size.top, size.width, size.height);
}

void GraphicsEngine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getId());
}

void GraphicsEngine::setUniformBuffer(const UniformBufferPtr& buffer, unsigned int slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

void GraphicsEngine::setShaderProgram(const ShaderProgramPtr& program)
{
	glUseProgram(program->getId());
}

void GraphicsEngine::drawTriangles(const TriangleType& triangleType, int vertexCount, int offset)
{
	auto glTriangleType = GL_TRIANGLES;

	switch (triangleType)
	{
		case TriangleType::TriangleList:
			glTriangleType = GL_TRIANGLES;
			break;

		case TriangleType::TriangleStrip:
			glTriangleType = GL_TRIANGLE_STRIP;
			break;
	}

	glDrawArrays(glTriangleType, offset, vertexCount);
}

void GraphicsEngine::drawIndexedTriangles(const TriangleType& triangleType, int indicesCount)
{
	auto glTriangleType = GL_TRIANGLES;

	switch (triangleType)
	{
		case TriangleType::TriangleList:
			glTriangleType = GL_TRIANGLES;
			break;

		case TriangleType::TriangleStrip:
			glTriangleType = GL_TRIANGLE_STRIP;
			break;
	}

	glDrawElements(glTriangleType, indicesCount, GL_UNSIGNED_INT, nullptr);
	CheckGLError("glDrawElements");
}

void GraphicsEngine::setPointLights(const ShaderProgramPtr& shader, const int count, const Vector3* positions, const Vector3* colors)
{
	int location = glGetUniformLocation(shader->getId(), "point_light_positions");
	glUniform3fv(location, count, &positions[0].m_x);
	if (location == -1) std::cerr << "Uniform 'position' not found!" << std::endl;

	location = glGetUniformLocation(shader->getId(), "point_light_colors");
	glUniform3fv(location, count, &colors[0].m_x);
	if (location == -1) std::cerr << "Uniform 'color' not found!" << std::endl;

	CheckGLError("setPointLights");
}

void GraphicsEngine::setEyePosition(const ShaderProgramPtr& shader, const Vector3 eyePosition)
{
	int location = glGetUniformLocation(shader->getId(), "eye_position");
	glUniform3f(location, eyePosition.m_x, eyePosition.m_y, eyePosition.m_z);
	if (location == -1) std::cerr << "Uniform 'eye' not found!" << std::endl;
}

void GraphicsEngine::setMaterialAttributes(const ShaderProgramPtr& shader, const Vector3& color, const int& shininess)
{
	int location = glGetUniformLocation(shader->getId(), "material_ka");
	glUniform3fv(location, 1, &color.m_x);
	if (location == -1) std::cerr << "Uniform 'ka' not found!" << std::endl;

	location = glGetUniformLocation(shader->getId(), "material_kd");
	glUniform3fv(location, 1, &color.m_x);
	if (location == -1) std::cerr << "Uniform 'kd' not found!" << std::endl;

	location = glGetUniformLocation(shader->getId(), "material_ks");
	glUniform3fv(location, 1, &color.m_x);
	if (location == -1) std::cerr << "Uniform 'ks' not found!" << std::endl;

	location = glGetUniformLocation(shader->getId(), "material_shininess");
	glUniform1i(location, shininess);
	if (location == -1) std::cerr << "Uniform 'shiny' not found!" << std::endl;
}

const char* glErrorToString(GLenum error) {
	switch (error) {
	case GL_NO_ERROR:          return "GL_NO_ERROR";
	case GL_INVALID_ENUM:      return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:     return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
	case GL_OUT_OF_MEMORY:     return "GL_OUT_OF_MEMORY";
	case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
	default:                   return "UNKNOWN_ERROR";
	}
}

void GraphicsEngine::CheckGLError(const char* context) {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		printf("[OpenGL Error] %s: %s\n", context, glErrorToString(error));
	}
}

#pragma once
#include <memory>
#include <Prerequisites.h>

class Window;
class GraphicsEngine;
class Game
{
public:
	Game();
	~Game();

	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnQuit();

	void Run();
	void Quit();

protected:
	bool m_isRunning = true;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;
	std::unique_ptr<Window> m_display = nullptr;
	
	VertexArrayObjectPtr m_triangleVAO;
	ShaderProgramPtr m_shader;
};
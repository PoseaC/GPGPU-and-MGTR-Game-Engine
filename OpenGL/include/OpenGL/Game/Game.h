#pragma once
#include <memory>
#include <Prerequisites.h>
#include <chrono>

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
	
	VertexArrayObjectPtr m_polygonVAO;
	ShaderProgramPtr m_shader;
	UniformBufferPtr m_uniform;
	
	std::chrono::system_clock::time_point m_previousTime;
	float m_scale = 0;
	float m_deltaTime;

private:
	void computeDeltaTime();
};
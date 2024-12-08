#pragma once
#include <memory>
#include <Prerequisites.h>
#include <OpenGL/Math/Mat4.h>
#include <chrono>

class EntitySystem;
class Window;
class GraphicsEngine;
class Game
{
public:
	Game();
	virtual ~Game();

	void Run();
	void Quit();

	EntitySystem* getEntitySystem();

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnQuit();

	bool m_isRunning = true;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;
	std::unique_ptr<Window> m_display;
	std::unique_ptr<EntitySystem> m_entitySystem;
	
	VertexArrayObjectPtr m_polygonVAO;
	ShaderProgramPtr m_shader;
	UniformBufferPtr m_uniform;
	
	std::chrono::system_clock::time_point m_previousTime;
	float m_animationStep = 0;
	float m_deltaTime;

	Mat4 m_world;
	Mat4 m_projection;

private:
	void OnUpdateInternal();
	void computeDeltaTime();
};
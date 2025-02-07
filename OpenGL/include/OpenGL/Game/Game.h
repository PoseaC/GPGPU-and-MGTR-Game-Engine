#pragma once
#include <memory>
#include <Prerequisites.h>
#include <OpenGL/Math/Mat4.h>
#include <OpenGL/Graphics/GraphicsEngine.h>
#include <chrono>

class EntitySystem;
class Window;
class GraphicsEngine;
class InputSystem;
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
	std::unique_ptr<InputSystem> m_inputSystem;
	ShaderProgramPtr m_shader;
	UniformBufferPtr m_uniform;
	
	std::chrono::system_clock::time_point m_previousTime;
	float m_deltaTime;

	Mat4 m_projection;
	Mat4 m_view;
	Vector3 m_pointLightsPositions[1] = {
		Vector3(0, 1, 1)
	};
	Vector3 m_pointLightsColors[1] = {
		Vector3(1, 1, 1)
	};

private:
	void OnUpdateInternal();
	void computeDeltaTime();
};
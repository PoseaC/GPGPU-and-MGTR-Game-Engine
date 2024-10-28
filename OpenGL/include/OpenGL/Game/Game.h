#pragma once
#include <memory>
#include <Prerequisites.h>

using namespace std;

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
	unique_ptr<GraphicsEngine> m_graphicsEngine;
	unique_ptr<Window> m_display = nullptr;
	
	VertexArrayObjectPtr m_triangleVAO;
};
#pragma once
#include "memory"

class Window;
class Game
{
public:
	Game();
	~Game();

	void run();
	void quit();
protected:
	bool m_is_running = true;
	std::unique_ptr<Window> m_display = nullptr;
};


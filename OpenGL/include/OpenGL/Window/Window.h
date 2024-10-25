#pragma once
class Window
{
public:
	Window(int resolutionX, int resolutionY);
	~Window();

	void makeCurrentContext();
	void present(bool vsync);

private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
};


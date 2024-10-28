#pragma once
#include<OpenGL/Math/Rect.h>

class Window
{
public:
	Window(int resolutionX, int resolutionY);
	~Window();

	Rect getInnerSize();

	void makeCurrentContext();
	void present(bool vsync);

private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
};


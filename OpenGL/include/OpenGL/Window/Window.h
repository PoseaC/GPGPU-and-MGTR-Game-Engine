#pragma once
#include<OpenGL/Math/Rect.h>

class Window
{
public:
	Window(int resolutionX, int resolutionY);
	~Window();

	Rect getInnerSize();
	virtual void OnFocus();
	virtual void OnLoseFocus();

	void makeCurrentContext();
	void present(bool vsync);
	bool m_focused = true;

private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
};


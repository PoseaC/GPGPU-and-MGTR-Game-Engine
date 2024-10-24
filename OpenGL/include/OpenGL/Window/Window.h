#pragma once
class Window
{
public:
	Window(int resolutionX, int resolutionY);
	~Window();

	void OnDestroy();
	bool IsClosed();
private:
	void* m_handle = nullptr;
};


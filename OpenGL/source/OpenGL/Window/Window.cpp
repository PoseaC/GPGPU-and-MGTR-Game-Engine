#include "OpenGL/Window/Window.h"
#include "Windows.h"
#include "assert.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			Window* window = (Window*) GetWindowLongPtr(hwnd,GWLP_USERDATA);
			window->OnDestroy();
			break;
		}

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return NULL;
}

Window::Window(int resolutionX, int resolutionY)
{
	WNDCLASSEX window = {};
	window.cbSize = sizeof(WNDCLASSEX);
	window.lpszClassName = L"Window";
	window.lpfnWndProc = &WndProc;

	assert(RegisterClassEx(&window));

	RECT window_content = {0, 0, resolutionX, resolutionY};
	AdjustWindowRect(&window_content, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(NULL, L"Window", L"GPGPU and MGTR Game Engine", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
								window_content.right - window_content.left, window_content.bottom - window_content.top, NULL, NULL, NULL, NULL);

	assert(m_handle);

	SetWindowLongPtr((HWND) m_handle, GWLP_USERDATA, (LONG_PTR) this);

	ShowWindow((HWND) m_handle, SW_SHOW);
	UpdateWindow((HWND) m_handle);
}

Window::~Window()
{
	DestroyWindow((HWND) m_handle);
}

void Window::OnDestroy()
{
	m_handle = nullptr;
}

bool Window::IsClosed()
{
	return !m_handle;
}

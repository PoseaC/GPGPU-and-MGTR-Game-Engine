#pragma once
#include <OpenGL/Math/Point.h>

class InputListener
{
public:
	InputListener() {}
	~InputListener() {}

	virtual void OnKeyDown(int keycode) = 0;
	virtual void OnKeyUp(int keycode) = 0;
	virtual void OnMouseMove(const Point& deltaMousePos) = 0;
	virtual void OnMouseButtonDown(const Point& deltaMousePos, int button) = 0;
	virtual void OnMouseButtonUp(const Point& deltaMousePos, int button) = 0;
};
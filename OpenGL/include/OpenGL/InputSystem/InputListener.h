#pragma once

class InputListener
{
public:
	InputListener() {}
	~InputListener() {}

	virtual void OnKeyDown(int keycode) = 0;
	virtual void OnKeyUp(int keycode) = 0;
};
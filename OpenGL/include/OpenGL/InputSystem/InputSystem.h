#pragma once
#include <OpenGL/InputSystem/InputListener.h>
#include <vector>

class InputSystem
{
public:
	void Update();
	void AddListener(InputListener* listener);
	void RemoveListener(InputListener* listener);

private:
	std::vector<InputListener*> m_listeners;
	unsigned char m_keyStates[256] = {};
	unsigned char m_oldStates[256] = {};
};


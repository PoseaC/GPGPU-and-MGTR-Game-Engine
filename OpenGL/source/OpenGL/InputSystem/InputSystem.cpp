#include <OpenGL/InputSystem/InputSystem.h>
#include <Windows.h>

void InputSystem::Update()
{
	POINT currentMousePos = {};
	::GetCursorPos(&currentMousePos);

	if (m_firstTime)
	{
		m_oldMousePos = Point(currentMousePos.x, currentMousePos.y);
		m_firstTime = false;
	}

	if (currentMousePos.x != m_oldMousePos.m_x ||
		currentMousePos.y != m_oldMousePos.m_y)
	{
		auto it = m_listeners.begin();
		Point deltaMovement(currentMousePos.x - m_oldMousePos.m_x, currentMousePos.y - m_oldMousePos.m_y);

		while (it != m_listeners.end())
		{
			(*it)->OnMouseMove(deltaMovement);
			it++;
		}
	}
	m_oldMousePos = Point(currentMousePos.x, currentMousePos.y);

	if (::GetKeyboardState(m_keyStates))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// if highest bit is set the key is pressed
			if (m_keyStates[i] & 128)
			{
				auto it = m_listeners.begin();

				while (it != m_listeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keyStates[i] != m_oldStates[i])
						{
							(*it)->OnMouseButtonDown(m_oldMousePos, 0);
						}
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keyStates[i] != m_oldStates[i])
						{
							(*it)->OnMouseButtonDown(m_oldMousePos, 1);
						}
					}
					else
					{
						(*it)->OnKeyDown(i);
					}

					it++;
				}
			}
			else
			{
				if (m_keyStates[i] != m_oldStates[i])
				{
					auto it = m_listeners.begin();

					while (it != m_listeners.end())
					{
						if (i == VK_LBUTTON)
						{
							(*it)->OnMouseButtonUp(m_oldMousePos, 0);
						}
						else if (i == VK_RBUTTON)
						{
							(*it)->OnMouseButtonUp(m_oldMousePos, 1);
						}
						else
						{
							(*it)->OnKeyUp(i);
						}
						it++;
					}
				}
			}
		}
		::memcpy(m_oldStates, m_keyStates, sizeof(unsigned char) * 256);
	}
}

void InputSystem::AddListener(InputListener* listener)
{
	m_listeners.emplace_back(listener);
}

void InputSystem::RemoveListener(InputListener* listener)
{
	auto it = m_listeners.begin();

	while (it != m_listeners.end())
	{
		if (*it == listener)
		{
			m_listeners.erase(it);
			break;
		}
		it++;
	}
}

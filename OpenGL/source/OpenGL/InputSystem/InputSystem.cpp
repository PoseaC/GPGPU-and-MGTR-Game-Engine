#include <OpenGL/InputSystem/InputSystem.h>
#include <Windows.h>

void InputSystem::Update()
{
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
					(*it)->OnKeyDown(i);
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
						(*it)->OnKeyUp(i);
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

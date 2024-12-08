#pragma once
#include "Player.h"
#include <OpenGL/All.h>

class SampleGame: public Game, public InputListener
{
public:
	SampleGame();
	~SampleGame();

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);

private:
	float m_elapsedSeconds = 0.0f;
	Player* m_player = nullptr;
	InputSystem m_inputSystem;

	// Inherited via InputListener
	virtual void OnKeyDown(int keycode) override;
	virtual void OnKeyUp(int keycode) override;
};


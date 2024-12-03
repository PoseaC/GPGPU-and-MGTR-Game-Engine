#pragma once
#include "Player.h"
#include<OpenGL/All.h>

class SampleGame: public Game
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
};


#pragma once
#include <OpenGL/All.h>

class Player: public Entity
{
public:
	Player();
	~Player();

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);

private:
	float m_elapsedSeconds = 0.0f;
	Entity* m_entity = nullptr;
};


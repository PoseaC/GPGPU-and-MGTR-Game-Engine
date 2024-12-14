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
	Mat4 m_transform;

	// Inherited via InputListener
	virtual void OnKeyDown(int keycode) override;
	virtual void OnKeyUp(int keycode) override;
	virtual void OnMouseMove(const Point& deltaMousePos) override;
	virtual void OnMouseButtonDown(const Point& deltaMousePos, int button) override;
	virtual void OnMouseButtonUp(const Point& deltaMousePos, int button) override;
};


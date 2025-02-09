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
	std::unique_ptr<Player> m_player;
	Mat4 m_cameraPos;
	float m_cameraMovingForward;
	float m_cameraMovingRight;
	float m_cameraMovingUp;
	float m_cameraRotationX;
	float m_cameraRotationY;
	float m_cameraSpeed = 2.0f;
	bool m_canSpawn = true;
	bool m_canFreezeSimulation = false;

	void SpawnObjects();

	// Inherited via InputListener
	virtual void OnKeyDown(int keycode) override;
	virtual void OnKeyUp(int keycode) override;
	virtual void OnMouseMove(const Point& deltaMousePos) override;
	virtual void OnMouseButtonDown(const Point& deltaMousePos, int button) override;
	virtual void OnMouseButtonUp(const Point& deltaMousePos, int button) override;
};


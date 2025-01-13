#pragma once
#include <OpenGL/All.h>

class Player: public Entity, public InputListener
{
public:
	Player();
	~Player();

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);

	// Inherited via InputListener
	virtual void OnKeyDown(int keycode) override;
	virtual void OnKeyUp(int keycode) override;
	virtual void OnMouseMove(const Point& deltaMousePos) override;
	virtual void OnMouseButtonDown(const Point& deltaMousePos, int button) override;
	virtual void OnMouseButtonUp(const Point& deltaMousePos, int button) override;

	virtual void OnCollisionStart(Entity* collider) override;
	virtual void OnCollisionEnd(Entity* collider) override;
	virtual void OnCollisionStay(Entity* collider) override;

	float m_deltaTime;
	float m_movingForward;
	float m_movingRight;
	float m_movingUp;
};


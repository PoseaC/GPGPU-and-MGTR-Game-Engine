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

	virtual void OnCollisionStart(Entity* collider, Vector3 collisionNormal) override;
	virtual void OnCollisionEnd(Entity* collider) override;
	virtual void OnCollisionStay(Entity* collider, Vector3 collisionNormal) override;

	float m_deltaTime;
	Vector3 m_velocity;
	float m_bounciness = 0.5f;
	float m_friction = 0.8f;
	float m_drag = 0.6f;
	bool m_applyGravity = true;
};


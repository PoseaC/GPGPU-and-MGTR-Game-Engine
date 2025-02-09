#pragma once
#include <OpenGL/All.h>

class Player: public Entity, public InputListener
{
public:
	Player(Vector3 boxSize) : Entity(boxSize) {}
	Player(float radius) : Entity(radius) {}
	Player(float radius, float cylinderHeight) : Entity(radius, cylinderHeight) {}
	~Player() {}

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);

	// Inherited via InputListener
	virtual void OnKeyDown(int keycode) override;
	virtual void OnKeyUp(int keycode) override;
	virtual void OnMouseMove(const Point& deltaMousePos) override;
	virtual void OnMouseButtonDown(const Point& deltaMousePos, int button) override;
	virtual void OnMouseButtonUp(const Point& deltaMousePos, int button) override;

	bool m_jumped = false;
};


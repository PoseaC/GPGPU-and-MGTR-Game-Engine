#pragma once
#include <OpenGL/All.h>

class StaticEntity: public Entity
{
public:
	StaticEntity();
	~StaticEntity();

protected:
	virtual void OnCreate();
	virtual void OnUpdate(float deltaTime);
};


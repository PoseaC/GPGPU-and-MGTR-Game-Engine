#pragma once
#include <OpenGL/Math/Vector4.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	void clear(const Vector4& color);
};


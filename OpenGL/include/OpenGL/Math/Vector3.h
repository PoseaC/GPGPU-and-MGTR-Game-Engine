#pragma once

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	float x = 0, y = 0, z = 0;
};
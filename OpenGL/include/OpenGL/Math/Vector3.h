#pragma once
#include <iostream>

class Vector3
{
public:
	Vector3() {}
	Vector3(float m_x, float m_y, float m_z) : m_x(m_x), m_y(m_y), m_z(m_z) {}

	Vector3 operator *(float num)
	{
		return Vector3(m_x * num, m_y * num, m_z * num);
	}

	Vector3 operator /(float num)
	{
		return Vector3(m_x / num, m_y / num, m_z / num);
	}

	Vector3 operator +(Vector3 vec)
	{
		return Vector3(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	Vector3 operator -(Vector3 vec)
	{
		return Vector3(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
	}

	Vector3 operator *(Vector3 vec)
	{
		return Vector3(m_x * vec.m_x, m_y * vec.m_y, m_z * vec.m_z);
	}

	Vector3 normalized()
	{
		return *this / length();
	}

	Vector3 operator-() const {
		return Vector3(-m_x, -m_y, -m_z);
	}

	float dot(Vector3 vec)
	{
		return m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z;
	}

	float length()
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	friend std::ostream& operator <<(std::ostream& os, const Vector3& vec3)
	{
		return os << "(" << vec3.m_x << ", " << vec3.m_y << ", " << vec3.m_z << ")";
	}

	float m_x = 0, m_y = 0, m_z = 0;
};
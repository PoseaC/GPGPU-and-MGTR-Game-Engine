#pragma once

class Vector3
{
public:
	Vector3() {}
	Vector3(float m_x, float m_y, float m_z) : m_x(m_x), m_y(m_y), m_z(m_z) {}

	Vector3 operator *(float num)
	{
		return Vector3(this->m_x * num, this->m_y * num, this->m_z * num);
	}

	Vector3 operator +(Vector3 vec)
	{
		return Vector3(this->m_x + vec.m_x, this->m_y + vec.m_y, this->m_z + vec.m_z);
	}

	float m_x = 0, m_y = 0, m_z = 0;
};
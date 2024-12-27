#pragma once

class Vector4
{
public:
	Vector4() {}
	Vector4(float x, float y, float z, float w): m_x(x), m_y(y), m_z(z), m_w(w) {}

	void cross(Vector4& v1, Vector4& v2, Vector4& v3)
	{
		this->m_x = v1.m_y * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) + v1.m_w * (v2.m_y * v3.m_z - v2.m_z * v3.m_y);
		this->m_y = -(v1.m_x * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_z - v3.m_x * v2.m_z));
		this->m_z = v1.m_x * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) - v1.m_y * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_y - v3.m_x * v2.m_y);
		this->m_w = -(v1.m_x * (v2.m_y * v3.m_z - v3.m_y * v2.m_z) - v1.m_y * (v2.m_x * v3.m_z - v3.m_x * v2.m_z) + v1.m_z * (v2.m_x * v3.m_y - v3.m_x * v2.m_y));
	}

	float m_x = 0, m_y = 0, m_z = 0, m_w = 0;
};
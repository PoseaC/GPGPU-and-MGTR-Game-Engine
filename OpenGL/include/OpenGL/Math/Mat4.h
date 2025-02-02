#pragma once
#include <Prerequisites.h>
#include <OpenGL/Math/Vector3.h>
#include <OpenGL/Math/Vector4.h>

class Mat4
{
public:
	Mat4() {}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(m_mat));
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setScale(const Vector3& scale)
	{
		m_mat[0][0] = scale.m_x;
		m_mat[1][1] = scale.m_y;
		m_mat[2][2] = scale.m_z;
	}

	void setTranslation(const Vector3& translation)
	{
		m_mat[3][0] = translation.m_x;
		m_mat[3][1] = translation.m_y;
		m_mat[3][2] = translation.m_z;
	}

	void setRotationX(float degrees)
	{
		m_mat[1][1] = cos(degrees);
		m_mat[1][2] = sin(degrees);
		m_mat[2][1] = -sin(degrees);
		m_mat[2][2] = cos(degrees);
	}

	void setRotationY(float degrees)
	{
		m_mat[0][0] = cos(degrees);
		m_mat[0][2] = -sin(degrees);
		m_mat[2][0] = sin(degrees);
		m_mat[2][2] = cos(degrees);
	}

	void setRotationZ(float degrees)
	{
		m_mat[0][0] = cos(degrees);
		m_mat[0][1] = sin(degrees);
		m_mat[1][0] = -sin(degrees);
		m_mat[1][1] = cos(degrees);
	}

	float getDeterminant()
	{
		Vector4 minor, v1, v2, v3;
		float det;

		v1 = Vector4(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		v2 = Vector4(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		v3 = Vector4(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);

		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.m_x + this->m_mat[1][3] * minor.m_y + this->m_mat[2][3] * minor.m_z +
			this->m_mat[3][3] * minor.m_w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Mat4 out;
		Vector4 v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.m_x / det;
			out.m_mat[1][i] = pow(-1.0f, i) * v.m_y / det;
			out.m_mat[2][i] = pow(-1.0f, i) * v.m_z / det;
			out.m_mat[3][i] = pow(-1.0f, i) * v.m_w / det;
		}

		this->setMatrix(out);
	}

	void operator *= (const Mat4& matrix)
	{
		Mat4 out;

		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				for (auto k = 0; k < 4; k++)
				{
					out.m_mat[i][j] += m_mat[i][k] * matrix.m_mat[k][j];
				}
			}
		}

		*this = out;
	}

	void setMatrix(const Mat4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}

	Vector3 getZDirection()
	{
		return Vector3(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}

	Vector3 getXDirection()
	{
		return Vector3(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}

	Vector3 getTranslation()
	{
		return Vector3(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	void setPerspectiveFov(float degreesFOV, float aspect, float znear, float zfar)
	{
		float radiansFOV = degreesFOV * 3.14f / 180;
		float yscale = 1.0f / tan(radiansFOV / 2.0f);
		float xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	void setOrtho(float width, float height, float nearPlane, float farPlane)
	{
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (farPlane - nearPlane);
		m_mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	float m_mat[4][4] = {};
};
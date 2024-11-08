#pragma once
#include <Prerequisites.h>
#include <OpenGL/Math/Vector4.h>

class Mat4
{
public:
	Mat4(){}

	void setIdentity()
	{
		::memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setScale(const Vector4& scale)
	{
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void setTranslation(const Vector4& translation)
	{
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}

	void setRotationX(float degrees)
	{
		mat[1][1] = cos(degrees);
		mat[1][2] = sin(degrees);
		mat[2][1] = -sin(degrees);
		mat[2][2] = cos(degrees);
	}

	void setRotationY(float degrees)
	{
		mat[0][0] = cos(degrees);
		mat[0][2] = -sin(degrees);
		mat[2][0] = sin(degrees);
		mat[2][2] = cos(degrees);
	}

	void setRotationZ(float degrees)
	{
		mat[0][0] = cos(degrees);
		mat[0][1] = sin(degrees);
		mat[1][0] = -sin(degrees);
		mat[1][1] = cos(degrees);
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
					out.mat[i][j] += mat[i][k] * matrix.mat[k][j];
				}
			}
		}

		*this = out;
	}

	float mat[4][4] = {};
};
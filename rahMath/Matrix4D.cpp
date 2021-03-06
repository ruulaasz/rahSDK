#include "Matrix4D.h"
#include "PlatformMath.h"

namespace rah
{
	Matrix4D::Matrix4D()
	{
		math::Clear(*this);
	}

	Matrix4D::Matrix4D(const Matrix4D & _matrix)
	{
		*this = _matrix;
	}

	Matrix4D::~Matrix4D()
	{

	}

	Matrix4D Matrix4D::operator+(const Matrix4D & _Matrix4x4)
	{
		Matrix4D AditionMatrix = _Matrix4x4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] + (Line[j][i]);
			}
		}

		return AditionMatrix;
	}

	Matrix4D Matrix4D::operator-(const Matrix4D & _Matrix4x4)
	{
		Matrix4D AditionMatrix = _Matrix4x4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] - (Line[j][i]);
			}
		}

		return AditionMatrix;
	}

	Matrix4D Matrix4D::operator*(const Matrix4D & _Matrix4x4)
	{
		Matrix4D MultiplicationMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					MultiplicationMatrix.Line[j][i] += (Line[k][i] * _Matrix4x4.Line[j][k]);
				}
			}
		}

		return MultiplicationMatrix;
	}

	void Matrix4D::operator*=(const Matrix4D & _Matrix4x4)
	{
		Matrix4D MultiplicationMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					MultiplicationMatrix.Line[j][i] += (Line[k][i] * _Matrix4x4.Line[j][k]);
				}
			}
		}

		*this = MultiplicationMatrix;
	}

	Matrix4D Matrix4D::operator*(float _Value)
	{
		Matrix4D MultiplicationMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				MultiplicationMatrix.Line[j][i] = Line[j][i] * _Value;
			}
		}

		return MultiplicationMatrix;
	}

	void Matrix4D::operator+=(const Matrix4D & _Matrix4x4)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Line[j][i] += (_Matrix4x4.Line[j][i]);
			}
		}
	}

	void Matrix4D::operator-=(const Matrix4D & _Matrix4x4)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Line[j][i] -= (_Matrix4x4.Line[j][i]);
			}
		}
	}

	bool Matrix4D::operator!=(const Matrix4D & _Matrix4x4)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Line[j][i] != (_Matrix4x4.Line[j][i]))
				{
					return true;
				}
			}
		}

		return false;
	}
}
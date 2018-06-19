#include "Matrix3D.h"
#include <memory.h>

namespace rah
{
	Matrix3D::Matrix3D()
	{

	}

	Matrix3D::Matrix3D(const Matrix3D & _matrix)
	{
		*this = _matrix;
	}

	Matrix3D::~Matrix3D()
	{

	}

	Matrix3D Matrix3D::operator+(const Matrix3D & _Matrix3x3)
	{
		Matrix3D AditionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] + (_Matrix3x3.Line[j][i]);
			}
		}

		return AditionMatrix;
	}

	Matrix3D Matrix3D::operator-(const Matrix3D & _Matrix3x3)
	{
		Matrix3D SubtractionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				SubtractionMatrix.Line[j][i] = Line[j][i] - (_Matrix3x3.Line[j][i]);
			}
		}

		return SubtractionMatrix;
	}

	Matrix3D Matrix3D::operator*(const Matrix3D & _Matrix3x3)
	{
		Matrix3D MultiplicationMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					MultiplicationMatrix.Line[j][i] += (Line[k][i] * _Matrix3x3.Line[j][k]);
				}
			}
		}

		return MultiplicationMatrix;
	}

	Matrix3D Matrix3D::operator*(float _Value)
	{
		Matrix3D MultiplicationMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				MultiplicationMatrix.Line[j][i] = Line[j][i] * _Value;
			}
		}

		return MultiplicationMatrix;
	}

	void Matrix3D::operator+=(const Matrix3D & _Matrix3x3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Line[j][i] += (_Matrix3x3.Line[j][i]);
			}
		}
	}
	void Matrix3D::operator-=(const Matrix3D & _Matrix3x3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Line[j][i] -= (_Matrix3x3.Line[j][i]);
			}
		}
	}

	void Matrix3D::clear()
	{
		memset(this, 0, sizeof(Matrix3D));
	}

	void Matrix3D::identity()
	{
		clear();

		m00 = 1;
		m11 = 1;
		m22 = 1;
	}

	void Matrix3D::transpose()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Line[j][i] = Line[i][j];
			}
		}
	}

	void Matrix3D::scaleMatrix(float _x, float _y, float _z)
	{
		identity();

		m00 *= _x;
		m11 *= _y;
		m22 *= _z;
	}

	void Matrix3D::rotate(float _radians, math::Axis _axis)
	{
		identity();

		float fPreCalcCos = math::Cos(_radians);
		float fPreCalcSin = math::Sin(_radians);

		if (_axis == math::Axis_X)
		{
			m11 = fPreCalcCos;
			m12 = fPreCalcSin;
			m21 = -fPreCalcSin;
			m22 = fPreCalcCos;
		}

		if (_axis == math::Axis_Y)
		{
			m00 = fPreCalcCos;
			m20 = fPreCalcSin;
			m02 = -fPreCalcSin;
			m22 = fPreCalcCos;
		}

		if (_axis == math::Axis_Z)
		{
			m00 = fPreCalcCos;
			m01 = fPreCalcSin;
			m10 = -fPreCalcSin;
			m11 = fPreCalcCos;
		}
	}

	float Matrix3D::determinant()
	{
		return	((m00 * m11 * m22) + (m01 * m12 * m20) + (m02 * m10 * m21)) -
				((m02 * m11 * m20) + (m01 * m10 * m22) + (m00 * m12 * m21));
	}
}
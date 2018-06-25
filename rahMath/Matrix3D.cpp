#include "Matrix3D.h"

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
}
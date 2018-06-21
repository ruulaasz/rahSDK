#include "Matrix4D.h"
#include <memory.h>

namespace rah
{
	Matrix4D::Matrix4D()
	{

	}

	rah::Matrix4D::Matrix4D(const Matrix4D & _matrix)
	{
		*this = _matrix;
	}

	Matrix4D::~Matrix4D()
	{

	}

	Matrix4D rah::Matrix4D::operator+(const Matrix4D & _Matrix4x4)
	{
		Matrix4D AditionMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] + (Line[j][i]);
			}
		}

		return AditionMatrix;
	}

	Matrix4D rah::Matrix4D::operator-(const Matrix4D & _Matrix4x4)
	{
		Matrix4D AditionMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] - (Line[j][i]);
			}
		}

		return AditionMatrix;
	}

	Matrix4D rah::Matrix4D::operator*(const Matrix4D & _Matrix4x4)
	{
		Matrix4D MultiplicationMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					MultiplicationMatrix.Line[j][i] += (Line[k][i] * Line[j][k]);
				}
			}
		}

		return MultiplicationMatrix;
	}

	Matrix4D rah::Matrix4D::operator*(float _Value)
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

	void rah::Matrix4D::operator+=(const Matrix4D & _Matrix4x4)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Line[j][i] += (Line[j][i]);
			}
		}
	}

	void rah::Matrix4D::operator-=(const Matrix4D & _Matrix4x4)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Line[j][i] -= (Line[j][i]);
			}
		}
	}

	void Matrix4D::clear()
	{
		memset(this, 0, sizeof(Matrix4D));
	}

	void Matrix4D::identity()
	{
		clear();

		m00 = 1;
		m11 = 1;
		m22 = 1;
		m33 = 1;
	}

	void Matrix4D::transpose()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Line[j][i] = Line[i][j];
			}
		}
	}

	void Matrix4D::scaleMatrix(float _x, float _y, float _z)
	{
		identity();

		m00 *= _x;
		m11 *= _y;
		m22 *= _z;
	}

	void Matrix4D::rotate(float _radians, math::Axis _axis)
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

	void Matrix4D::translateMatrix(float _x, float _y, float _z)
	{
		identity();

		Line[0][3] = _x;
		Line[1][3] = _y;
		Line[2][3] = _z;
	}

	float Matrix4D::determinant()
	{
		return  m03 * m12 * m21 * m30 - m02 * m13 * m21 * m30 -
			m03 * m11 * m22 * m30 + m01 * m13 * m22 * m30 +
			m02 * m11 * m23 * m30 - m01 * m12 * m23 * m30 -
			m03 * m12 * m20 * m31 + m02 * m13 * m20 * m31 +
			m03 * m10 * m22 * m31 - m00 * m13 * m22 * m31 -
			m02 * m10 * m23 * m31 + m00 * m12 * m23 * m31 +
			m03 * m11 * m20 * m32 - m01 * m13 * m20 * m32 -
			m03 * m10 * m21 * m32 + m00 * m13 * m21 * m32 +
			m01 * m10 * m23 * m32 - m00 * m11 * m23 * m32 -
			m02 * m11 * m20 * m33 + m01 * m12 * m20 * m33 +
			m02 * m10 * m21 * m33 - m00 * m12 * m21 * m33 -
			m01 * m10 * m22 * m33 + m00 * m11 * m22 * m33;
	}

	void Matrix4D::inverse()
	{
		float d = ((m00 * m11 - m01 * m10) * (m22 * m33 - m23 * m32) -
			(m00 *m12 - m02 * m10) * (m21 * m33 - m23 * m31) +
			(m00 * m13 - m03 * m10) * (m21 * m32 - m22 * m31) +
			(m01 * m12 - m02 * m11) * (m20 * m33 - m23 * m30) -
			(m01 *m13 - m03 *m11) * (m20 *m32 - m22 * m30) +
			(m02 * m13 - m03 *m12) * (m20 * m31 - m21 * m30));

		d = 1 / d;

		m00 = d *(m11 * (m22 * m33 - m23 * m32) +
		m12 * (m23 * m31 - m21 * m33) +
		m13 * (m21 * m32 - m22 * m31));

		m01 = d *(m21 * (m02 * m33 - m03 * m32) +
		m22 * (m03 * m31 - m01 * m33) +
		m23 * (m01 * m32 - m02 * m31));

		m02 = d *(m31 * (m02 * m13 - m03 * m12) +
		m32 * (m03 * m11 - m01 * m13) +
		m33 * (m01 * m12 - m02 * m11));

		m03 = d *(m01 * (m13 * m22 - m12 * m23) +
		m02 * (m11 * m23 - m13 * m21) +
		m03 * (m12 * m21 - m11 * m22));

		m10 = d *(m12 * (m20 * m33 - m23 * m30) +
		m13 * (m22 * m30 - m20 * m32) +
		m10 * (m23 * m32 - m22 * m33));

		m11 = d *(m22 * (m00 * m33 - m03 * m30) +
		m23 * (m02 * m30 - m00 * m32) +
		m20 * (m03 * m32 - m02 * m33));

		m12 = d *(m32 * (m00 * m13 - m03 * m10) +
		m33 * (m02 * m10 - m00 * m12) +
		m30 * (m03 * m12 - m02 * m13));

		m13 = d *(m02 * (m13 * m20 - m10 * m23) +
		m03 * (m10 * m22 - m12 * m20) +
		m00 * (m12 * m23 - m13 * m22));

		m20 = d *(m13 * (m20 * m31 - m21 * m30) +
		m10 * (m21 * m33 - m23 * m31) +
		m11 * (m23 * m30 - m20 * m33));

		m21 = d *(m23 * (m00 * m31 - m01 * m30) +
		m20 * (m01 * m33 - m03 * m31) +
		m21 * (m03 * m30 - m00 * m33));

		m22 = d *(m33 * (m00 * m11 - m01 * m10) +
		m30 * (m01 * m13 - m03 * m11) +
		m31 * (m03 * m10 - m00 * m13));

		m23 = d *(m03 * (m11 * m20 - m10 * m21) +
		m00 * (m13 * m21 - m11 * m23) +
		m01 * (m10 * m23 - m13 * m20));

		m30 = d *(m10 * (m22 * m31 - m21 * m32) +
		m11 * (m20 * m32 - m22 * m30) +
		m12 * (m21 * m30 - m20 * m31));

		m31 = d *(m20 * (m02 * m31 - m01 * m32) +
		m21 * (m00 * m32 - m02 * m30) +
		m22 * (m01 * m30 - m00 * m31));

		m32 = d *(m30 * (m02 * m11 - m01 * m12) +
		m31 * (m00 * m12 - m02 * m10) +
		m32 * (m01 * m10 - m00 * m11));

		m33 = d *(m00 * (m11 * m22 - m12 * m21) +
			m01 * (m12 * m20 - m10 * m22) +
			m02 * (m10 * m21 - m11 * m20));
	}

	void Matrix4D::lookAtLH(Vector4D _eye, Vector4D _at, Vector4D _up)
	{
		//Direccion, que es una linea de ti al objeto, no esta perpendicular al vector y de vista
		Vector4D vDir, vRight, vUp, vOffset;
		vDir = _at - _eye;
		vDir.normalize();

		//Perpendicularizar el vector vista hacia up y vista
		vRight = _up;
		vRight.cross(vDir);
		vRight.normalize();

		//Con esto, el productro cruz con derecha y arriva me da el nuevo vector arriva, que es perpendicular al vector que esta hacia el objeto
		vUp = vDir;
		vUp.cross(vRight);

		//Esta ultima transformacion terminara convirtiendo los objetos a mi origen, suponiendo que yo soy el origen
		vOffset = Vector4D(
			-vRight.dot(_eye), 
			-vUp.dot(_eye),
			-vDir.dot(_eye),
			0.f);

	m00 = vRight.x;
	m10 = vRight.y;
	m20 = vRight.z;
	m30 = vOffset.x;

	m01 = vUp.x;
	m11 = vUp.y;
	m21 = vUp.z;
	m31 = vOffset.y;

	m02 = vDir.x;
	m12 = vDir.y;
	m22 = vDir.z;
	m32 = vOffset.z;

	m03 = 0;
	m13 = 0;
	m23 = 0;
	m33 = 1;

	}

	void Matrix4D::perspectiveFovLH(float _FovAngleY, float _AspectRatio, float _NearZ, float _FarZ)
	{
		//Cotagente
		float h = 1.0f / math::Tan(_FovAngleY / 2);
		float w = h / _AspectRatio;

		m00 = w;
		m11 = h;
		m22 = _FarZ / (_FarZ - _NearZ);
		m32 = -_NearZ * _FarZ / (_FarZ - _NearZ);
		m23 = 1;
	}
}
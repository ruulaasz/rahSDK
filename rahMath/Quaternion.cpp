#include "Quaternion.h"
#include "Matrix4D.h"
#include "Vector4D.h"
#include "Radians.h"
#include "PlatformMath.h"
namespace rah
{
	const Quaternion Quaternion::Indentity = Quaternion(1.0f);

	Quaternion::Quaternion(Vector4D _vector)
	{
		X = _vector.x;
		Y = _vector.y;
		Z = _vector.z;
		W = _vector.w;
	}
	Quaternion::~Quaternion()
	{
	}
	float Quaternion::DotProduct(Quaternion _SecondQuaterion)
	{
		return W*_SecondQuaterion.W + X*_SecondQuaterion.X + Y*_SecondQuaterion.Y + Z*_SecondQuaterion.Z;
	}
	float Quaternion::Magnitude()
	{
		return rah::math::Sqrt(X*X + Y*Y + Z*Z + W*W);
	}
	Quaternion Quaternion::Normalize()
	{
		return Quaternion(*this / Magnitude());
	}
	Quaternion Quaternion::Inverse()
	{
		Quaternion ResultQuat(-X, -Y, -Z, W);
		return ResultQuat / Magnitude();
	}
	Quaternion Quaternion::Slerp(const Quaternion _SecondQuaterion, float _time)
	{
		Quaternion ResultQuat;
		Quaternion SecondQuaternion = _SecondQuaterion;

		float cosOmega = DotProduct(_SecondQuaterion);

		if (cosOmega < 0.0f)
		{
			SecondQuaternion.X = -SecondQuaternion.X;
			SecondQuaternion.Y = -SecondQuaternion.Y;
			SecondQuaternion.Z = -SecondQuaternion.Z;
			SecondQuaternion.W = -SecondQuaternion.W;
			cosOmega = -cosOmega;
		}

		float k0, k1;

		if (cosOmega > 0.9999f)
		{
			k0 = 1.0f - _time;
			k1 = _time;
		}
		else
		{
			float sinOmega = rah::math::Sqrt(1.0f - cosOmega*cosOmega);
			float omega = rah::math::ArcTan2(sinOmega, cosOmega);
			float oneOverSinOmega = 1.0f / sinOmega;
			k0 = rah::math::Sin((1.0f - _time) * omega) * oneOverSinOmega;
			k1 = rah::math::Sin(_time * omega) * oneOverSinOmega;
		}

		ResultQuat.X = X*k0 + SecondQuaternion.X*k1;
		ResultQuat.Y = Y*k0 + SecondQuaternion.Y*k1;
		ResultQuat.Z = Z*k0 + SecondQuaternion.Z*k1;
		ResultQuat.W = W*k0 + SecondQuaternion.W*k1;

		return ResultQuat;
	}
	Matrix4D Quaternion::QuaternionToMatrix4D()
	{
		Matrix4D CalMatrix;
		CalMatrix = rah::math::Identity4D();
		float PowX = X*X;
		float PowY = Y*Y;
		float PowZ = Z*Z;

		CalMatrix.m00 = 1.0f - 2.0f * PowY - 2 * PowZ;
		CalMatrix.m01 = 2.0f * X * Y - 2.0f * Z * W;
		CalMatrix.m02 = 2.0f * X * Z + 2.0f * Y * W;

		CalMatrix.m10 = 2.0f * X * Y + 2 * Z * W;
		CalMatrix.m11 = 1.0f - 2.0f * PowX - 2 * PowZ;
		CalMatrix.m12 = 2 * Y * Z - 2 * X * W;

		CalMatrix.m20 = 2.0f * X * Z - 2.0f * Y * W;
		CalMatrix.m21 = 2.0f * Y * Z + 2.0f + 2.0f * X * W;
		CalMatrix.m22 = 1.0f - 2.0f * PowX - 2.0f * PowY;

		return CalMatrix;
	}
	Quaternion Quaternion::Matrix4DToQuaternion(const Matrix4D _Matrix)
	{
		//Determinamos cual tiene el mayor numero absoluto
		float fourXSquareMinus1 = _Matrix.m00 - _Matrix.m11 - _Matrix.m22;
		float fourYSquareMinus1 = _Matrix.m11 - _Matrix.m00 - _Matrix.m22;
		float fourZSquareMinus1 = _Matrix.m22 - _Matrix.m00 - _Matrix.m11;
		float fourWSquareMinus1 = _Matrix.m00 + _Matrix.m11 + _Matrix.m22;

		int BiggestIndex = 0;
		float fourBiggestSquaredMinus1 = fourWSquareMinus1;
		if (fourXSquareMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquareMinus1;
			BiggestIndex = 1;
		}
		if (fourYSquareMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquareMinus1;
			BiggestIndex = 2;
		}
		if (fourZSquareMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquareMinus1;
			BiggestIndex = 3;
		}

		//Hacemos la raiz cuadrada y la division
		float biggestVal = rah::math::Sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		float mult = 0.25f / biggestVal;

		//Lo aplicamos al quaternion
		Quaternion ResultQuaternion;
		switch (BiggestIndex)
		{
		case 0:
			ResultQuaternion.X = (_Matrix.m12 - _Matrix.m21) * mult;
			ResultQuaternion.Y = (_Matrix.m20 - _Matrix.m02) * mult;
			ResultQuaternion.Z = (_Matrix.m01 - _Matrix.m10) * mult;
			ResultQuaternion.W = biggestVal;
			break;
		case 1:
			ResultQuaternion.X = biggestVal;
			ResultQuaternion.Y = (_Matrix.m01 + _Matrix.m10) * mult;
			ResultQuaternion.Z = (_Matrix.m20 + _Matrix.m02) * mult;
			ResultQuaternion.W = (_Matrix.m12 - _Matrix.m21) * mult;
			break;
		case 2:
			ResultQuaternion.X = (_Matrix.m01 + _Matrix.m10) * mult;
			ResultQuaternion.Y = biggestVal;
			ResultQuaternion.Z = (_Matrix.m12 + _Matrix.m21) * mult;
			ResultQuaternion.W = (_Matrix.m20 - _Matrix.m02) * mult;
			break;
		case 3:
			ResultQuaternion.X = (_Matrix.m20 + _Matrix.m02) * mult;
			ResultQuaternion.Y = (_Matrix.m12 + _Matrix.m21) * mult;
			ResultQuaternion.Z = biggestVal;
			ResultQuaternion.W = (_Matrix.m01 - _Matrix.m10) * mult;
			break;
		default:
			break;
		}

		return ResultQuaternion;
	}
	Quaternion Quaternion::EulerToQuaternion(Radians & _Heading, Radians & _Attitude, Radians & _Bank)
	{
		float c1 = rah::math::Cos(_Heading / 2.f);
		float c2 = rah::math::Cos(_Attitude / 2.f);
		float c3 = rah::math::Cos(_Bank / 2.f);
		float s1 = rah::math::Sin(_Heading / 2.f);
		float s2 = rah::math::Sin(_Attitude / 2.f);
		float s3 = rah::math::Sin(_Bank / 2.f);

		return Quaternion(s1*s2*c3 + c1*c2*s3, s1*c2*c3 + c1*s2*s3, c1*s2*c3 - s1*c2*s3, c1*c2*c3 - s1*s2*s3);
	}
	Quaternion Quaternion::operator=(Vector4D _vector)
	{
		X = _vector.x;
		Y = _vector.y;
		Z = _vector.z;
		W = _vector.w;
		return *this;
	}
	Quaternion Quaternion::operator=(Matrix4D _Matrix)
	{
		*this = Matrix4DToQuaternion(_Matrix);
		return *this;
	}
	Quaternion Quaternion::operator+(Quaternion _Quaternion)
	{
		return Quaternion(X + _Quaternion.X, Y + _Quaternion.Y, Z + _Quaternion.Z, W + _Quaternion.W);
	}
	Quaternion Quaternion::operator-(Quaternion _Quaternion)
	{
		return Quaternion(X - _Quaternion.X, Y - _Quaternion.Y, Z - _Quaternion.Z, W - _Quaternion.W);
	}
	Quaternion Quaternion::operator*(Quaternion _Quaternion)
	{
		return Quaternion(X * _Quaternion.X, Y * _Quaternion.Y, Z * _Quaternion.Z, W * _Quaternion.W);
	}
	Quaternion Quaternion::operator/(Quaternion _Quaternion)
	{
		return Quaternion(X / _Quaternion.X, Y / _Quaternion.Y, Z / _Quaternion.Z, W / _Quaternion.W);
	}
	Quaternion Quaternion::operator/(float _valor)
	{
		return Quaternion(X / _valor, Y / _valor, Z / _valor, W / _valor);
	}
	bool Quaternion::operator==(Quaternion _Quaternion)
	{
		return (X == _Quaternion.X && Y == _Quaternion.Y && Z == _Quaternion.Z && W == _Quaternion.W);
	}
	bool Quaternion::operator!=(Quaternion _Quaternion)
	{
		return(X != _Quaternion.X && Y != _Quaternion.Y && Z != _Quaternion.Z && W != _Quaternion.W);
	}
	bool Quaternion::operator>(Quaternion _Quaternion)
	{
		return(X > _Quaternion.X && Y > _Quaternion.Y && Z > _Quaternion.Z && W > _Quaternion.W);
	}
	bool Quaternion::operator>=(Quaternion _Quaternion)
	{
		return(X >= _Quaternion.X && Y >= _Quaternion.Y && Z >= _Quaternion.Z && W >= _Quaternion.W);
	}
	bool Quaternion::operator<(Quaternion _Quaternion)
	{
		return(X < _Quaternion.X && Y < _Quaternion.Y && Z < _Quaternion.Z && W < _Quaternion.W);
	}
	bool Quaternion::operator<=(Quaternion _Quaternion)
	{
		return(X <= _Quaternion.X && Y <= _Quaternion.Y && Z <= _Quaternion.Z && W <= _Quaternion.W);
	}
}

#pragma once

#include <cmath>
#include <memory.h>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3D.h"
#include "Matrix4D.h"

namespace rah
{
	namespace math
	{
		typedef unsigned int uint;
		typedef unsigned char int8;

		enum Axis
		{
			Axis_X=0, 
			Axis_Y,
			Axis_Z
		};

		/**
		* PI Constant
		*
		*/
		static const float PI = atan(1.0f) * 4;

		/**
		* Degrees to radians constant
		*
		*/
		static const float DEG_TO_RAD = PI / 180;

		/**
		* Radians to degrees constant
		*
		*/
		static const float RAD_TO_DEG = 180 / PI;

		/**
		* Returns the sin of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T Sin(T _value) { return sin(_value); };
		/**
		* Returns the sin of a float value
		* Works in radians
		*
		*/
		template<>
		static float Sin(float _value) { return sinf(_value); };

		/**
		* Returns the cos of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T Cos(T _value) { return cos(_value); };		
		/**
		* Returns the cos of a float value
		* Works in radians
		*
		*/
		template<>
		static float Cos(float _value) { return cosf(_value); };	

		/**
		* Returns the tan of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T Tan(T _value) { return tan(_value); };		
		/**
		* Returns the tan of a float value
		* Works in radians
		*
		*/
		template<>
		static float Tan(float _value) { return tanf(_value); };	

		/**
		* Returns the arcsin of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T ArcSin(T _value) { return asin(_value); };	
		/**
		* Returns the arcsin of a float value
		* Works in radians
		*
		*/
		template<>
		static float ArcSin(float _value) { return asinf(_value); };

		/**
		* Returns the arccos of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T ArcCos(T _value) { return acos(_value); };	
		/**
		* Returns the arccos of a float value
		* Works in radians
		*
		*/
		template<>
		static float ArcCos(float _value) { return acosf(_value); };

		/**
		* Returns the arctan of any given value
		* Works in radians
		*
		*/
		template<typename T>
		static T ArcTan(T _value) { return atan(_value); };	
		/**
		* Returns the arctan of a float value
		* Works in radians
		*
		*/
		template<>
		static float ArcTan(float _value) { return atanf(_value); };
	
		/**
		* Returns the squareroot of any given value
		*
		*/
		template<typename T>
		static T Sqrt(T _value) { return sqrt(_value); };
		/**
		* Returns the squareroot of a float value
		*
		*/
		template<>
		static float Sqrt(float _value)		
		{
			return sqrt(_value);			
		}

		/**
		* Returns the inverse squareroot of any given value
		*
		*/
		template<typename T>
		static T InvSqrt(T _value) { return (1 / sqrt(_value)); };
		/**
		* Returns the inverse squareroot of a float value
		*
		*/
		template<>
		static float InvSqrt(float _value) { return (1 / sqrt(_value)); };

		/**
		* Returns the square of any given value
		*
		*/
		template<typename T>
		static T Square(T _value) { return (_value*_value); };
		/**
		* Returns the square of a float value
		*
		*/
		template<>
		static float Square(float _value)							
		{
			return (_value*_value);			
		}

		/**
		* Elevates a given value to a given power
		*
		*/
		template<typename T, typename Y>
		static T Pow(T _value, Y _pow) { return pow(_value, _pow); };
		/**
		* Elevates a float value to a given power
		*
		*/
		template<>
		static float Pow(float _value, int _power) { return pow(_value, _power); };

		/**
		* Calculates the factorial of a given value
		*
		*/
		static unsigned Factorial(unsigned _value)
		{
			if (_value == 1)
				return 1;
			else
				return _value* Factorial(_value - 1);
		};

		/**
		* Returns the smallest value between 2 values
		*
		*/
		template<typename T>
		static T Min(T _value1, T _value2) { return (_value1 <= _value2 ? _value1 : _value2); };

		/**
		* Returns the bigest value between 2 values
		*
		*/
		template<typename T>
		static T Max(T _value1, T _value2) { return (_value1 >= _value2 ? _value1 : _value2); };

		/**
		* Returns the smallest value between 3 values
		*
		*/
		template<typename T>
		static T Min3(T _value1, T _value2, T _value3) { return Min(Min(_value1, _value2), _value3); };

		/**
		* Returns the bigest value between 3 values
		*
		*/
		template<typename T>
		static T Max3(T _value1, T _value2, T _value3) { return Max(Max(_value1, _value2), _value3); };

		/**
		* Vector Length
		*/
		static float Length(Vector2D& _Vector)
		{
			return Sqrt(Square(_Vector.x) + Square(_Vector.y));
		}

		static float Length(Vector3D& _Vector)
		{
			return Sqrt(Square(_Vector.x) + Square(_Vector.y) + Square(_Vector.z));
		}

		static float Length(Vector4D& _Vector)
		{
			return Sqrt(Square(_Vector.x) + Square(_Vector.y) + Square(_Vector.z) + Square(_Vector.w));
		}

		/**
		* Vector Length Squared
		*/
		static float LengthSquared(Vector2D& _Vector)
		{
			return Square(_Vector.x) + Square(_Vector.y);
		}

		static float LengthSquared(Vector3D& _Vector)
		{
			return Square(_Vector.x) + Square(_Vector.y) + Square(_Vector.z);
		}

		static float LengthSquared(Vector4D& _Vector)
		{
			return Square(_Vector.x) + Square(_Vector.y) + Square(_Vector.z) + Square(_Vector.w);
		}

		/**
		* Vector Dot
		*/
		static float Dot(Vector2D& _Vector, Vector2D& _Vector2)
		{
			return((_Vector.x * _Vector2.x) + (_Vector.y * _Vector2.y));
		}

		static float Dot(Vector3D& _Vector, Vector3D& _Vector2)
		{
			return((_Vector.x * _Vector2.x) + (_Vector.y * _Vector2.y) + (_Vector.z * _Vector2.z));
		}

		static float Dot(Vector4D& _Vector, Vector4D& _Vector2)
		{
			return((_Vector.x * _Vector2.x) + (_Vector.y * _Vector2.y) + (_Vector.z * _Vector2.z) + (_Vector.w * _Vector2.w));
		}

		/**
		* Vector Normalize
		*/
		static void Normalize(Vector2D& _Vector)
		{
			float length = Length(_Vector);

			if (length != 0)
				_Vector.x /= length, _Vector.y /= length;
		}

		static void Normalize(Vector3D& _Vector)
		{
			float length = Length(_Vector);

			if (length != 0)
				_Vector.x /= length, _Vector.y /= length, _Vector.z /= length;
		}

		static void Normalize(Vector4D& _Vector)
		{
			float length = Length(_Vector);

			if (length != 0)
				_Vector.x /= length, _Vector.y /= length, _Vector.z /= length, _Vector.w /= length;
		}

		/**
		* Vector Escalate
		*/
		static void Escalate(Vector2D& _Vector, float _scalar)
		{
			Normalize(_Vector);

			_Vector.x *= _scalar, _Vector.y *= _scalar;
		}

		static void Escalate(Vector3D& _Vector, float _scalar)
		{
			Normalize(_Vector);

			_Vector.x *= _scalar, _Vector.y *= _scalar, _Vector.z *= _scalar;
		}

		static void Escalate(Vector4D& _Vector, float _scalar)
		{
			Normalize(_Vector);

			_Vector.x *= _scalar, _Vector.y *= _scalar, _Vector.z *= _scalar, _Vector.w *= _scalar;
		}

		/**
		* Vector Truncate
		*/
		static void Truncate(Vector2D& _Vector, float _max)
		{
			float mag = Length(_Vector);

			if (mag > _max)
				Escalate(_Vector, _max);
		}

		static void Truncate(Vector3D& _Vector, float _max)
		{
			float mag = Length(_Vector);

			if (mag > _max)
				Escalate(_Vector, _max);
		}

		static void Truncate(Vector4D& _Vector, float _max)
		{
			float mag = Length(_Vector);

			if (mag > _max)
				Escalate(_Vector, _max);
		}

		/**
		* Vector Cross
		*/
		static Vector3D CrossProduct(const Vector3D& _Vector, const Vector3D& _Vector2)
		{
			return Vector3D
			{
				_Vector.y * _Vector2.z - _Vector.z * _Vector2.y,
				_Vector.z * _Vector2.x - _Vector.x * _Vector2.z,
				_Vector.x * _Vector2.y - _Vector.y * _Vector2.x
			};
		}

		static Vector4D CrossProduct(const Vector4D& _Vector, const Vector4D& _Vector2)
		{
			return Vector4D
			{
				_Vector.y * _Vector2.z - _Vector.z * _Vector2.y,
				_Vector.z * _Vector2.x - _Vector.x * _Vector2.z,
				_Vector.x * _Vector2.y - _Vector.y * _Vector2.x
			};
		}

		/**
		* Vector Clear
		*/
		static void Clear(Vector2D& _Vector)
		{
			memset(&_Vector, 0, sizeof(Vector2D));
		}

		static void Clear(Vector3D& _Vector)
		{
			memset(&_Vector, 0, sizeof(Vector3D));
		}

		static void Clear(Vector4D& _Vector)
		{
			memset(&_Vector, 0, sizeof(Vector4D));
		}

		/**
		* Matrix Clear
		*/
		static void Clear(Matrix3D& _Matrix)
		{
			memset(&_Matrix, 0, sizeof(Matrix3D));
		}

		static void Clear(Matrix4D& _Matrix)
		{
			memset(&_Matrix, 0, sizeof(Matrix4D));
		}

		/**
		* Matrix Identity
		*/
		static Matrix3D Identity3D()
		{
			Matrix3D IdentityMatrix;

			Clear(IdentityMatrix);

			IdentityMatrix.m00 = 1;
			IdentityMatrix.m11 = 1;
			IdentityMatrix.m22 = 1;

			return IdentityMatrix;
		}

		static Matrix4D Identity4D()
		{
			Matrix4D IdentityMatrix;

			Clear(IdentityMatrix);

			IdentityMatrix.m00 = 1;
			IdentityMatrix.m11 = 1;
			IdentityMatrix.m22 = 1;
			IdentityMatrix.m33 = 1;

			return IdentityMatrix;
		}

		/**
		* Matrix Transpose
		*/
		static Matrix3D Transpose(const Matrix3D& _Matrix3x3)
		{
			Matrix3D TransposeMatrix;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					TransposeMatrix.Line[j][i] = _Matrix3x3.Line[i][j];
				}
			}

			return TransposeMatrix;
		}

		static Matrix4D Transpose(const Matrix4D& _Matrix4x4)															
		{
			Matrix4D TransposeMatrix;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					TransposeMatrix.Line[i][j] = _Matrix4x4.Line[j][i];
				}
			}

			return TransposeMatrix;
		}

		/**
		* Matrix Scalar
		*/
		static Matrix3D ScalarMatrix3x3(float _X, float _Y, float _Z)
		{
			Matrix3D ScalarMatrix = Identity3D();

			ScalarMatrix.m00 *= _X;
			ScalarMatrix.m11 *= _Y;
			ScalarMatrix.m22 *= _Z;

			return ScalarMatrix;
		}

		static Matrix4D ScalarMatrix4x4(float _X, float _Y, float _Z)
		{
			Matrix4D ScalarMatrix = Identity4D();

			ScalarMatrix.Line[0][0] = _X;
			ScalarMatrix.Line[1][1] = _Y;
			ScalarMatrix.Line[2][2] = _Z;

			return ScalarMatrix;
		}

		/**
		* Matrix Translation
		*/
		static Matrix4D TranslationMatrix4x4(float _X, float _Y, float _Z)
		{
			Matrix4D TranslationMatrix = Identity4D();

			TranslationMatrix.Line[0][3] = _X;
			TranslationMatrix.Line[1][3] = _Y;
			TranslationMatrix.Line[2][3] = _Z;

			return TranslationMatrix;
		}

		/**
		* Matrix Rotation
		*/
		static Matrix3D RotationMatrix3x3(float _radians, Axis _Axis)
		{
			Matrix3D RotationMatrix = Identity3D();

			float fPreCalcCos = Cos(_radians);
			float fPreCalcSin = Sin(_radians);

			if (_Axis == Axis_X)
			{
				RotationMatrix.m11 = fPreCalcCos;
				RotationMatrix.m12 = fPreCalcSin;
				RotationMatrix.m21 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (_Axis == Axis_Y)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m20 = fPreCalcSin;
				RotationMatrix.m02 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (_Axis == Axis_Z)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m01 = fPreCalcSin;
				RotationMatrix.m10 = -fPreCalcSin;
				RotationMatrix.m11 = fPreCalcCos;
			}

			return Matrix3D(RotationMatrix);
		}

		static Matrix4D RotationMatrix4x4(float _radians, Axis _Axis)
		{
			Matrix4D RotationMatrix = Identity4D();

			float fPreCalcCos = Cos(_radians);
			float fPreCalcSin = Sin(_radians);

			if (_Axis == Axis_X)
			{
				RotationMatrix.Line[1][1] = fPreCalcCos;
				RotationMatrix.Line[2][2] = fPreCalcCos;
				RotationMatrix.Line[1][2] = fPreCalcSin;
				RotationMatrix.Line[2][1] = -fPreCalcSin;
			}

			if (_Axis == Axis_Y)
			{
				RotationMatrix.Line[0][0] = fPreCalcCos;
				RotationMatrix.Line[2][2] = fPreCalcCos;
				RotationMatrix.Line[0][2] = -fPreCalcSin;
				RotationMatrix.Line[2][0] = fPreCalcSin;
			}

			if (_Axis == Axis_Z)
			{
				RotationMatrix.Line[0][0] = fPreCalcCos;
				RotationMatrix.Line[1][1] = fPreCalcCos;
				RotationMatrix.Line[0][1] = fPreCalcSin;
				RotationMatrix.Line[1][0] = -fPreCalcSin;
			}

			return Matrix4D(RotationMatrix);
		}

		/**
		* Matrix Determinant
		*/
		static float DeterminantMatrix(const Matrix3D& _Matrix3x3)	
		{
			return	((_Matrix3x3.m00 * _Matrix3x3.m11 * _Matrix3x3.m22) + (_Matrix3x3.m01 * _Matrix3x3.m12 * _Matrix3x3.m20) + (_Matrix3x3.m02 * _Matrix3x3.m10 * _Matrix3x3.m21)) -
				((_Matrix3x3.m02 * _Matrix3x3.m11 * _Matrix3x3.m20) + (_Matrix3x3.m01 * _Matrix3x3.m10 * _Matrix3x3.m22) + (_Matrix3x3.m00 * _Matrix3x3.m12 * _Matrix3x3.m21));
		}

		static float DeterminantMatrix(const Matrix4D& _Matrix4x4)					
		{
			return  _Matrix4x4.m03 * _Matrix4x4.m12 * _Matrix4x4.m21 * _Matrix4x4.m30 - _Matrix4x4.m02 * _Matrix4x4.m13 * _Matrix4x4.m21 * _Matrix4x4.m30 -
				_Matrix4x4.m03 * _Matrix4x4.m11 * _Matrix4x4.m22 * _Matrix4x4.m30 + _Matrix4x4.m01 * _Matrix4x4.m13 * _Matrix4x4.m22 * _Matrix4x4.m30 +
				_Matrix4x4.m02 * _Matrix4x4.m11 * _Matrix4x4.m23 * _Matrix4x4.m30 - _Matrix4x4.m01 * _Matrix4x4.m12 * _Matrix4x4.m23 * _Matrix4x4.m30 -
				_Matrix4x4.m03 * _Matrix4x4.m12 * _Matrix4x4.m20 * _Matrix4x4.m31 + _Matrix4x4.m02 * _Matrix4x4.m13 * _Matrix4x4.m20 * _Matrix4x4.m31 +
				_Matrix4x4.m03 * _Matrix4x4.m10 * _Matrix4x4.m22 * _Matrix4x4.m31 - _Matrix4x4.m00 * _Matrix4x4.m13 * _Matrix4x4.m22 * _Matrix4x4.m31 -
				_Matrix4x4.m02 * _Matrix4x4.m10 * _Matrix4x4.m23 * _Matrix4x4.m31 + _Matrix4x4.m00 * _Matrix4x4.m12 * _Matrix4x4.m23 * _Matrix4x4.m31 +
				_Matrix4x4.m03 * _Matrix4x4.m11 * _Matrix4x4.m20 * _Matrix4x4.m32 - _Matrix4x4.m01 * _Matrix4x4.m13 * _Matrix4x4.m20 * _Matrix4x4.m32 -
				_Matrix4x4.m03 * _Matrix4x4.m10 * _Matrix4x4.m21 * _Matrix4x4.m32 + _Matrix4x4.m00 * _Matrix4x4.m13 * _Matrix4x4.m21 * _Matrix4x4.m32 +
				_Matrix4x4.m01 * _Matrix4x4.m10 * _Matrix4x4.m23 * _Matrix4x4.m32 - _Matrix4x4.m00 * _Matrix4x4.m11 * _Matrix4x4.m23 * _Matrix4x4.m32 -
				_Matrix4x4.m02 * _Matrix4x4.m11 * _Matrix4x4.m20 * _Matrix4x4.m33 + _Matrix4x4.m01 * _Matrix4x4.m12 * _Matrix4x4.m20 * _Matrix4x4.m33 +
				_Matrix4x4.m02 * _Matrix4x4.m10 * _Matrix4x4.m21 * _Matrix4x4.m33 - _Matrix4x4.m00 * _Matrix4x4.m12 * _Matrix4x4.m21 * _Matrix4x4.m33 -
				_Matrix4x4.m01 * _Matrix4x4.m10 * _Matrix4x4.m22 * _Matrix4x4.m33 + _Matrix4x4.m00 * _Matrix4x4.m11 * _Matrix4x4.m22 * _Matrix4x4.m33;
		}

		/**
		* Matrix Inverse
		*/
		static Matrix4D InverseMatrix4D(Matrix4D& _Matrix4x4)
		{
			float d = ((_Matrix4x4.m00 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m10) * (_Matrix4x4.m22 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m32) -
				(_Matrix4x4.m00 *_Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m10) * (_Matrix4x4.m21 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m31) +
				(_Matrix4x4.m00 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m10) * (_Matrix4x4.m21 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m31) +
				(_Matrix4x4.m01 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m11) * (_Matrix4x4.m20 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m30) -
				(_Matrix4x4.m01 *_Matrix4x4.m13 - _Matrix4x4.m03 *_Matrix4x4.m11) * (_Matrix4x4.m20 *_Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m30) +
				(_Matrix4x4.m02 * _Matrix4x4.m13 - _Matrix4x4.m03 *_Matrix4x4.m12) * (_Matrix4x4.m20 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m30));

			d = 1 / d;

			Matrix4D Inv;

			Inv.m00 = d *(_Matrix4x4.m11 * (_Matrix4x4.m22 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m32) +
				_Matrix4x4.m12 * (_Matrix4x4.m23 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m33) +
				_Matrix4x4.m13 * (_Matrix4x4.m21 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m31));

			Inv.m01 = d *(_Matrix4x4.m21 * (_Matrix4x4.m02 * _Matrix4x4.m33 - _Matrix4x4.m03 * _Matrix4x4.m32) +
				_Matrix4x4.m22 * (_Matrix4x4.m03 * _Matrix4x4.m31 - _Matrix4x4.m01 * _Matrix4x4.m33) +
				_Matrix4x4.m23 * (_Matrix4x4.m01 * _Matrix4x4.m32 - _Matrix4x4.m02 * _Matrix4x4.m31));

			Inv.m02 = d *(_Matrix4x4.m31 * (_Matrix4x4.m02 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m12) +
				_Matrix4x4.m32 * (_Matrix4x4.m03 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m13) +
				_Matrix4x4.m33 * (_Matrix4x4.m01 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m11));

			Inv.m03 = d *(_Matrix4x4.m01 * (_Matrix4x4.m13 * _Matrix4x4.m22 - _Matrix4x4.m12 * _Matrix4x4.m23) +
				_Matrix4x4.m02 * (_Matrix4x4.m11 * _Matrix4x4.m23 - _Matrix4x4.m13 * _Matrix4x4.m21) +
				_Matrix4x4.m03 * (_Matrix4x4.m12 * _Matrix4x4.m21 - _Matrix4x4.m11 * _Matrix4x4.m22));

			Inv.m10 = d *(_Matrix4x4.m12 * (_Matrix4x4.m20 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m30) +
				_Matrix4x4.m13 * (_Matrix4x4.m22 * _Matrix4x4.m30 - _Matrix4x4.m20 * _Matrix4x4.m32) +
				_Matrix4x4.m10 * (_Matrix4x4.m23 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m33));

			Inv.m11 = d *(_Matrix4x4.m22 * (_Matrix4x4.m00 * _Matrix4x4.m33 - _Matrix4x4.m03 * _Matrix4x4.m30) +
				_Matrix4x4.m23 * (_Matrix4x4.m02 * _Matrix4x4.m30 - _Matrix4x4.m00 * _Matrix4x4.m32) +
				_Matrix4x4.m20 * (_Matrix4x4.m03 * _Matrix4x4.m32 - _Matrix4x4.m02 * _Matrix4x4.m33));

			Inv.m12 = d *(_Matrix4x4.m32 * (_Matrix4x4.m00 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m10) +
				_Matrix4x4.m33 * (_Matrix4x4.m02 * _Matrix4x4.m10 - _Matrix4x4.m00 * _Matrix4x4.m12) +
				_Matrix4x4.m30 * (_Matrix4x4.m03 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m13));

			Inv.m13 = d *(_Matrix4x4.m02 * (_Matrix4x4.m13 * _Matrix4x4.m20 - _Matrix4x4.m10 * _Matrix4x4.m23) +
				_Matrix4x4.m03 * (_Matrix4x4.m10 * _Matrix4x4.m22 - _Matrix4x4.m12 * _Matrix4x4.m20) +
				_Matrix4x4.m00 * (_Matrix4x4.m12 * _Matrix4x4.m23 - _Matrix4x4.m13 * _Matrix4x4.m22));

			Inv.m20 = d *(_Matrix4x4.m13 * (_Matrix4x4.m20 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m30) +
				_Matrix4x4.m10 * (_Matrix4x4.m21 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m31) +
				_Matrix4x4.m11 * (_Matrix4x4.m23 * _Matrix4x4.m30 - _Matrix4x4.m20 * _Matrix4x4.m33));

			Inv.m21 = d *(_Matrix4x4.m23 * (_Matrix4x4.m00 * _Matrix4x4.m31 - _Matrix4x4.m01 * _Matrix4x4.m30) +
				_Matrix4x4.m20 * (_Matrix4x4.m01 * _Matrix4x4.m33 - _Matrix4x4.m03 * _Matrix4x4.m31) +
				_Matrix4x4.m21 * (_Matrix4x4.m03 * _Matrix4x4.m30 - _Matrix4x4.m00 * _Matrix4x4.m33));

			Inv.m22 = d *(_Matrix4x4.m33 * (_Matrix4x4.m00 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m10) +
				_Matrix4x4.m30 * (_Matrix4x4.m01 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m11) +
				_Matrix4x4.m31 * (_Matrix4x4.m03 * _Matrix4x4.m10 - _Matrix4x4.m00 * _Matrix4x4.m13));

			Inv.m23 = d *(_Matrix4x4.m03 * (_Matrix4x4.m11 * _Matrix4x4.m20 - _Matrix4x4.m10 * _Matrix4x4.m21) +
				_Matrix4x4.m00 * (_Matrix4x4.m13 * _Matrix4x4.m21 - _Matrix4x4.m11 * _Matrix4x4.m23) +
				_Matrix4x4.m01 * (_Matrix4x4.m10 * _Matrix4x4.m23 - _Matrix4x4.m13 * _Matrix4x4.m20));

			Inv.m30 = d *(_Matrix4x4.m10 * (_Matrix4x4.m22 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m32) +
				_Matrix4x4.m11 * (_Matrix4x4.m20 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m30) +
				_Matrix4x4.m12 * (_Matrix4x4.m21 * _Matrix4x4.m30 - _Matrix4x4.m20 * _Matrix4x4.m31));

			Inv.m31 = d *(_Matrix4x4.m20 * (_Matrix4x4.m02 * _Matrix4x4.m31 - _Matrix4x4.m01 * _Matrix4x4.m32) +
				_Matrix4x4.m21 * (_Matrix4x4.m00 * _Matrix4x4.m32 - _Matrix4x4.m02 * _Matrix4x4.m30) +
				_Matrix4x4.m22 * (_Matrix4x4.m01 * _Matrix4x4.m30 - _Matrix4x4.m00 * _Matrix4x4.m31));

			Inv.m32 = d *(_Matrix4x4.m30 * (_Matrix4x4.m02 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m12) +
				_Matrix4x4.m31 * (_Matrix4x4.m00 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m10) +
				_Matrix4x4.m32 * (_Matrix4x4.m01 * _Matrix4x4.m10 - _Matrix4x4.m00 * _Matrix4x4.m11));

			Inv.m33 = d *(_Matrix4x4.m00 * (_Matrix4x4.m11 * _Matrix4x4.m22 - _Matrix4x4.m12 * _Matrix4x4.m21) +
				_Matrix4x4.m01 * (_Matrix4x4.m12 * _Matrix4x4.m20 - _Matrix4x4.m10 * _Matrix4x4.m22) +
				_Matrix4x4.m02 * (_Matrix4x4.m10 * _Matrix4x4.m21 - _Matrix4x4.m11 * _Matrix4x4.m20));

			return Inv;
		}

		/**
		* Matrix LookAtLH
		*/
		static Matrix4D LookAtLH(Vector3D _Eye, Vector3D _Focus, Vector3D _Up)
		{
			//Direccion, que es una linea de ti al objeto, no esta perpendicular al vector y de vista
			Vector3D vDir, vRight, vUp, vOffset;
			vDir = _Focus - _Eye;
			Normalize(vDir);

			//Perpendicularizar el vector vista hacia up y vista
			vRight = CrossProduct(_Up, vDir);
			Normalize(vRight);

			//Con esto, el productro cruz con derecha y arriva me da el nuevo vector arriva, que es perpendicular al vector que esta hacia el objeto
			vUp = CrossProduct(vDir, vRight);

			//Esta ultima transformacion terminara convirtiendo los objetos a mi origen, suponiendo que yo soy el origen
			vOffset = Vector3D(
				-Dot(vRight, _Eye), //Esta en sentido contrario porque queremos que se conviertan hacia la camara, no al revez
				-Dot(vUp, _Eye),
				-Dot(vDir, _Eye));

			Matrix4D MV;
			MV.m00 = vRight.x;
			MV.m10 = vRight.y;
			MV.m20 = vRight.z;
			MV.m30 = vOffset.x;

			MV.m01 = vUp.x;
			MV.m11 = vUp.y;
			MV.m21 = vUp.z;
			MV.m31 = vOffset.y;

			MV.m02 = vDir.x;
			MV.m12 = vDir.y;
			MV.m22 = vDir.z;
			MV.m32 = vOffset.z;

			MV.m03 = 0;
			MV.m13 = 0;
			MV.m23 = 0;
			MV.m33 = 1;

			return MV;
		}

		static Matrix4D LookAtLH(Vector4D _Eye, Vector4D _Focus, Vector4D _Up)
		{
			//Direccion, que es una linea de ti al objeto, no esta perpendicular al vector y de vista
			Vector4D vDir, vRight, vUp, vOffset;
			vDir = _Focus - _Eye;
			Normalize(vDir);

			//Perpendicularizar el vector vista hacia up y vista
			vRight = CrossProduct(_Up, vDir);
			Normalize(vRight);

			//Con esto, el productro cruz con derecha y arriva me da el nuevo vector arriva, que es perpendicular al vector que esta hacia el objeto
			vUp = CrossProduct(vDir, vRight);

			//Esta ultima transformacion terminara convirtiendo los objetos a mi origen, suponiendo que yo soy el origen
			vOffset = Vector4D(
				-Dot(vRight, _Eye), //Esta en sentido contrario porque queremos que se conviertan hacia la camara, no al revez
				-Dot(vUp, _Eye),
				-Dot(vDir, _Eye));

			Matrix4D MV;
			MV.m00 = vRight.x;
			MV.m10 = vRight.y;
			MV.m20 = vRight.z;
			MV.m30 = vOffset.x;

			MV.m01 = vUp.x;
			MV.m11 = vUp.y;
			MV.m21 = vUp.z;
			MV.m31 = vOffset.y;

			MV.m02 = vDir.x;
			MV.m12 = vDir.y;
			MV.m22 = vDir.z;
			MV.m32 = vOffset.z;

			MV.m03 = 0;
			MV.m13 = 0;
			MV.m23 = 0;
			MV.m33 = 1;

			return MV;
		}

		/**
		* Matrix PerspectiveFovLH
		*/
		static Matrix4D PerspectiveFovLH(float _FovAngleY, float _AspectRatio, float _NearZ, float _FarZ)
		{
			//Vamos a comprimir, entre mas sea el angulo, metemos mas geometria a la pantalla
			Matrix4D MP;

			//Cotagente
			float h = 1.0f / Tan(_FovAngleY / 2);
			float w = h / _AspectRatio;

			MP.m00 = w;
			MP.m11 = h;
			MP.m22 = _FarZ / (_FarZ - _NearZ);
			MP.m32 = -_NearZ * _FarZ / (_FarZ - _NearZ);
			MP.m23 = 1;

			return MP;
		}
	}
}
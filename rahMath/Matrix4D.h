#pragma once
#include "PlatformMath.h"
#include "Vector4D.h"

namespace rah
{
	/**
	* A 3D float Matrix class
	*
	*/
	class Matrix4D
	{
	public:
		Matrix4D();
		Matrix4D(const Matrix4D &_matrix);
		virtual ~Matrix4D();

		union
		{
			struct
			{
				float	m00, m01, m02, m03,
					m10, m11, m12, m13,
					m20, m21, m22, m23,
					m30, m31, m32, m33;
			};
			float Line[4][4];
			float Matrix[16];
		};

		Matrix4D operator+	(const Matrix4D& _Matrix4x4);
		Matrix4D operator-	(const Matrix4D& _Matrix4x4);
		Matrix4D operator*	(const Matrix4D& _Matrix4x4);
		Matrix4D operator*	(float _Value);
		void operator+=		(const Matrix4D& _Matrix4x4);
		void operator-=		(const Matrix4D& _Matrix4x4);

		/**
		* Reset the matrix elements to 0.f
		*
		*/
		void clear();

		/**
		* transforms this matrix to a identity matrix
		*
		*/
		void identity();

		/**
		* transpose the matrix
		*
		*/
		void transpose();

		/**
		* transforms into a scalarmatrix
		*
		* @param _x
		* the x scale
		*
		* @param _y
		* the y scale
		*
		* @param _z
		* the z scale
		*
		*/
		void scaleMatrix(float _x, float _y, float _z);

		/**
		* rotate the matrix
		*
		* @param _radians
		* the number of radians to rotate
		*
		* @param _axis
		* the axis of rotation
		*
		*/
		void rotate(float _radians, math::Axis _axis);
		
		/**
		* transforms into a translate matrix
		*
		* @param _x
		* the x movement
		*
		* @param _y
		* the y movement
		*
		* @param _z
		* the z movement
		*
		*/
		void translateMatrix(float _x, float _y, float _z);

		/**
		* transpose the matrix
		*
		*@return float
		*this matrix determinant
		*
		*/
		float determinant();

		/**
		* inverse the matrix
		*
		*/
		void inverse();

		void lookAtLH(Vector4D _eye, Vector4D _at, Vector4D _up);

		void perspectiveFovLH(float _FovAngleY, float _AspectRatio, float _NearZ, float _FarZ);
	};
}
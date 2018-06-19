#pragma once
#include "PlatformMath.h"

namespace rah
{
	/**
	* A 3D float Matrix class
	*
	*/
	class Matrix3D
	{
	public:
		Matrix3D();
		Matrix3D(const Matrix3D &_matrix);
		virtual ~Matrix3D();

		/**
		* Matrix 3D structure
		*
		*/
		union
		{
			struct
			{
				float	m00, m01, m02,
					m10, m11, m12,
					m20, m21, m22;
			};

			float Line[3][3];
			float Matrix[9];
		};

		Matrix3D operator+	(const Matrix3D& _Matrix3x3);
		Matrix3D operator-	(const Matrix3D& _Matrix3x3);
		Matrix3D operator*	(const Matrix3D& _Matrix3x3);
		Matrix3D operator*	(float _Value);
		void operator+=		(const Matrix3D& _Matrix3x3);
		void operator-=		(const Matrix3D& _Matrix3x3);

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
		* transpose the matrix
		*
		*@return float
		*this matrix determinant
		*
		*/
		float determinant();
	};
}
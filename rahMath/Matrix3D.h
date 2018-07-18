#pragma once
#pragma warning(disable : 4201)
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
		~Matrix3D();

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
	};
}
#pragma warning(default : 4201)
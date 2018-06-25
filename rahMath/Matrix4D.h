#pragma once

namespace rah
{
	/**
	* A 4D float Matrix class
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
	};
}
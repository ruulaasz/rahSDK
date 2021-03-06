#pragma once

namespace rah
{
	class Vector3D;

	/**
	* A 4D float vector class
	*
	*/
	class Vector4D
	{
	public:
		explicit Vector4D(float _x = 0.f, float _y = 0.f, float _z = 0.f, float _w = 1.f);
		Vector4D(const Vector4D &_vector);
		Vector4D(const Vector3D& _vector);
		~Vector4D();

		/**
		* Operator overload
		*
		*/
		Vector4D operator- (const Vector4D& _vector);
		Vector4D operator+ (const Vector4D& _vector);
		Vector4D operator* (const Vector4D& _vector);
		void operator+= (const Vector4D& _vector);
		void operator-= (const Vector4D& _vector);
		Vector4D operator/ (const float& _value);
		void operator/= (const float& _value);
		bool operator== (const Vector4D& _vector);
		bool operator!= (const Vector4D& _vector);
		Vector4D operator* (const float& _value);
		void operator*= (const float& _value);
		float& operator[](const int idx);

		float x;
		float y;
		float z;
		float w;
	};
}
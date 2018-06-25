#pragma once

namespace rah
{
	/**
	* A 3D float vector class
	*
	*/
	class Vector3D
	{
	public:
		explicit Vector3D(float _x = 0.f, float _y = 0.f, float _z = 0.f);
		Vector3D(const Vector3D &_vector);
		virtual ~Vector3D();

		/**
		* Operator overload
		*
		*/
		Vector3D operator- (const Vector3D& _vector);
		Vector3D operator+ (const Vector3D& _vector);
		Vector3D operator* (const Vector3D& _vector);
		void operator+= (const Vector3D& _vector);
		void operator-= (const Vector3D& _vector);
		Vector3D operator/ (const float& _value);
		void operator/= (const float& _value);
		bool operator== (const Vector3D& _vector);
		bool operator!= (const Vector3D& _vector);
		Vector3D operator* (const float& _value);
		void operator*= (const float& _value);
		float& operator[](const int idx);

		float x;
		float y;
		float z;
	};
}
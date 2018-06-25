#pragma once

namespace rah
{
	/**
	* A 2D float vector class
	*
	*/
	class Vector2D
	{
	public:
		explicit Vector2D(float _x = 0.f, float _y = 0.f);
		Vector2D(const Vector2D &_vector);
		virtual ~Vector2D();

		/**
		* Operator overload
		*
		*/
		Vector2D operator- (const Vector2D& _vector);
		Vector2D operator+ (const Vector2D& _vector);
		Vector2D operator* (const Vector2D& _vector);
		void operator+= (const Vector2D& _vector);
		void operator-= (const Vector2D& _vector);
		Vector2D operator/ (const float& _value);
		void operator/= (const float& _value);
		bool operator== (const Vector2D& _vector);
		bool operator!= (const Vector2D& _vector);
		Vector2D operator* (const float& _value);
		void operator*= (const float& _value);
		float& operator[](const int idx);

		float x;
		float y;
	};
}
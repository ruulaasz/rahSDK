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

		/**
		* Dot product between this and another vector
		*
		* @param _vector
		* a 3D vector
		*
		*@return float
		*a vector scalar
		*
		*/
		float dot(const Vector2D &_vector);

		/**
		* Process the magnitude
		*
		*@return float
		*this vector magnitude
		*
		*/
		float length();

		/**
		* Process the squared magnitude
		*
		*@return float
		*this vector squared magnitude
		*
		*/
		float lengthSquared();

		/**
		* Normalize this vector
		*
		*/
		void normalize();

		/**
		* normalize and scale to a given magnitude
		*
		* @param _scalar
		* the value to which this vector will be scaled
		*
		*/
		void escalate(float _scalar);

		/**
		* if this vector magnitude exceeds the given value it get scalated to the given value
		*
		* @param _max
		* the value to which this vector will be scaled if his magnitude exceeds the value
		*
		*/
		void truncate(float _max);

		/**
		* Set the values to 0.0f
		*
		*/
		void clear();

		float x;
		float y;
	};
}
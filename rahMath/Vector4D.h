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
		explicit Vector4D(float _x = 0.f, float _y = 0.f, float _z = 0.f, float _w = 0.f);
		Vector4D(const Vector4D &_vector);
		Vector4D(Vector3D& _vector);
		virtual ~Vector4D();

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

		/**
		* Dot product between this and another vector
		*
		* @param _vector
		* a 4D vector
		*
		*@return float
		*a vector scalar
		*
		*/
		float dot(const Vector4D &_vector);

		/**
		* Cross product between this and another vector
		*
		* @param _vector
		* a 4D vector
		*
		*@return Vector4D
		*the result vector
		*
		*/
		Vector4D cross(const Vector4D &_vector);

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
		float z;
		float w;
	};
}


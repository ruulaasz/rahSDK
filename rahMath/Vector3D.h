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
		Vector3D& operator+= (const Vector3D& _vector);
		Vector3D& operator-= (const Vector3D& _vector);
		Vector3D operator/ (const float& _value);
		void operator/= (const float& _value);
		bool operator== (const Vector3D& _vector);
		bool operator!= (const Vector3D& _vector);
		Vector3D operator* (const float& _value);
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
		float dot(const Vector3D &_vector);

		/**
		* Cross product between this and another vector
		*
		* @param _vector
		* a 3D vector
		*
		*@return Vector3D
		*the result vector
		*
		*/
		Vector3D cross(const Vector3D &_vector);

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
	};
}
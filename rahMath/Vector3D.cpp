#include "Vector3D.h"

namespace rah
{
	Vector3D::Vector3D(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3D::Vector3D(const Vector3D & _vector)
	{
		x = _vector.x;
		y = _vector.y;
		z = _vector.z;
	}

	Vector3D::~Vector3D()
	{

	}

	void Vector3D::Set(float _x, float _y, float _z) 
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3D Vector3D::operator-(const Vector3D & _vector)
	{
		Vector3D result;

		result.x = x - _vector.x;
		result.y = y - _vector.y;
		result.z = z - _vector.z;

		return result;
	}

	Vector3D Vector3D::operator+(const Vector3D & _vector)
	{
		Vector3D result;

		result.x = x + _vector.x;
		result.y = y + _vector.y;
		result.z = z + _vector.z;

		return result;
	}

	Vector3D Vector3D::operator*(const Vector3D & _vector)
	{
		Vector3D result;

		result.x = x * _vector.x;
		result.y = y * _vector.y;
		result.z = z * _vector.z;

		return result;
	}

	void Vector3D::operator+=(const Vector3D & _vector)
	{
		x += _vector.x;
		y += _vector.y;
		z += _vector.z;
	}

	void Vector3D::operator-=(const Vector3D & _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		z -= _vector.z;
	}

	Vector3D Vector3D::operator/(const float & _value)
	{
		return Vector3D(x / _value, y / _value, z / _value);
	}

	void Vector3D::operator/=(const float & _value)
	{
		x /= _value;
		y /= _value;
		z /= _value;
	}

	bool Vector3D::operator==(const Vector3D & _vector)
	{
		if (x != _vector.x)
			return false;
		if (y != _vector.y)
			return false;
		if (z != _vector.z)
			return false;

		return true;
	}

	bool Vector3D::operator!=(const Vector3D & _vector)
	{
		if (x != _vector.x)
			return true;
		if (y != _vector.y)
			return true;
		if (z != _vector.z)
			return true;

		return false;
	}

	Vector3D Vector3D::operator*(const float & _value)
	{
		return Vector3D(x * _value, y * _value, z * _value);
	}

	void Vector3D::operator*=(const float & _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
	}

	float & Vector3D::operator[](const int idx)
	{
		return (&x)[idx];
	}
}
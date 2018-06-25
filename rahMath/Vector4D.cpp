#include "Vector4D.h"
#include "Vector3D.h"

namespace rah
{
	rah::Vector4D::Vector4D(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	rah::Vector4D::Vector4D(const Vector4D & _vector)
	{
		x = _vector.x;
		y = _vector.y;
		z = _vector.z;
		w = _vector.w;
	}

	Vector4D::Vector4D(Vector3D & _vector)
	{
		x = _vector.x;
		y = _vector.y;
		z = _vector.z;
	}

	Vector4D::~Vector4D()
	{

	}

	Vector4D Vector4D::operator-(const Vector4D & _vector)
	{
		Vector4D result;

		result.x = x - _vector.x;
		result.y = y - _vector.y;
		result.z = z - _vector.z;
		result.w = w - _vector.w;

		return result;
	}

	Vector4D Vector4D::operator+(const Vector4D & _vector)
	{
		Vector4D result;

		result.x = x + _vector.x;
		result.y = y + _vector.y;
		result.z = z + _vector.z;
		result.w = w + _vector.w;

		return result;
	}

	Vector4D Vector4D::operator*(const Vector4D & _vector)
	{
		Vector4D result;

		result.x = x * _vector.x;
		result.y = y * _vector.y;
		result.z = z * _vector.z;
		result.w = w * _vector.w;

		return result;
	}

	void Vector4D::operator+=(const Vector4D & _vector)
	{
		x += _vector.x;
		y += _vector.y;
		z += _vector.z;
		w += _vector.w;
	}

	void Vector4D::operator-=(const Vector4D & _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		z -= _vector.z;
		w -= _vector.w;
	}

	Vector4D Vector4D::operator/(const float & _value)
	{
		return Vector4D(x / _value, y / _value, z / _value, w/_value);
	}

	void Vector4D::operator/=(const float & _value)
	{
		x /= _value;
		y /= _value;
		z /= _value;
		w /= _value;
	}

	bool Vector4D::operator==(const Vector4D & _vector)
	{
		if (x != _vector.x)
			return false;
		if (y != _vector.y)
			return false;
		if (z != _vector.z)
			return false;
		if (w != _vector.w)
			return false;

		return true;
	}

	bool Vector4D::operator!=(const Vector4D & _vector)
	{
		if (x != _vector.x)
			return true;
		if (y != _vector.y)
			return true;
		if (z != _vector.z)
			return true;
		if (w != _vector.w)
			return true;

		return false;
	}

	Vector4D Vector4D::operator*(const float & _value)
	{
		return Vector4D(x * _value, y * _value, z * _value, w * _value);
	}

	void Vector4D::operator*=(const float & _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
		w *= _value;
	}

	float & Vector4D::operator[](const int idx)
	{
		return (&x)[idx];
	}
}
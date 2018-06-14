#include "Vector4D.h"
#include "Vector3D.h"
#include "PlatformMath.h"

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

	float Vector4D::dot(const Vector4D & _vector)
	{
		return (x * _vector.x) + (y * _vector.y) + (z * _vector.z) + (w * _vector.w);
	}

	Vector4D Vector4D::cross(const Vector4D & _vector)
	{
		return Vector4D(y * _vector.z - z * _vector.y, z * _vector.x - x * _vector.z, x * _vector.y - y * _vector.x);
	}

	float Vector4D::length()
	{
		return math::Sqrt(math::Square(x) + math::Square(y) + math::Square(z) + math::Square(w));
	}

	void Vector4D::normalize()
	{
		float length = this->length();

		if (length != 0)
		{
			x /= length, y /= length, z /= length, w /= length;
		}
	}

	void Vector4D::escalate(float _scalar)
	{
		normalize();
		*this *= _scalar;
	}

	void Vector4D::truncate(float _max)
	{
		float mag = this->length();

		if (mag > _max)
			escalate(_max);
	}

	void Vector4D::clear()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	float Vector4D::lengthSquared()
	{
		return math::Square(x) + math::Square(y) + math::Square(z) + math::Square(w);
	}
}
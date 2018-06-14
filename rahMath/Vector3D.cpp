#include "Vector3D.h"
#include "PlatformMath.h"

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

	Vector3D & Vector3D::operator+=(const Vector3D & _vector)
	{
		x += _vector.x;
		y += _vector.y;
		z += _vector.z;

		return *this;
	}

	Vector3D & Vector3D::operator-=(const Vector3D & _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		z -= _vector.z;

		return *this;
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

	float Vector3D::dot(const Vector3D & _vector)
	{
		return (x * _vector.x) + (y * _vector.y) + (z * _vector.z);
	}

	Vector3D Vector3D::cross(const Vector3D & _vector)
	{
		Vector3D temp(y * _vector.z - z * _vector.y, z * _vector.x - x * _vector.z, x * _vector.y - y * _vector.x);
		return temp;
	}

	float Vector3D::length()
	{
		return math::Sqrt(math::Square(x) + math::Square(y) + math::Square(z));
	}

	float Vector3D::lengthSquared()
	{
		return math::Square(x) + math::Square(y) + math::Square(z);
	}

	void Vector3D::normalize()
	{
		float length = this->length();

		if (length != 0)
		{
			x /= length, y /= length, z /= length;
		}
	}

	void Vector3D::escalate(float _scalar)
	{
		normalize();
		*this *= _scalar;
	}

	void Vector3D::truncate(float _max)
	{
		float mag = this->length();

		if (mag > _max)
			escalate(_max);
	}

	void Vector3D::clear()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}
}
#include "Vector2D.h"
#include "PlatformMath.h"

namespace rah
{
	Vector2D::Vector2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2D::Vector2D(const Vector2D & _vector)
	{
		x = _vector.x;
		y = _vector.y;
	}

	Vector2D::~Vector2D()
	{

	}

	Vector2D Vector2D::operator-(const Vector2D & _vector)
	{
		Vector2D result;

		result.x = x - _vector.x;
		result.y = y - _vector.y;

		return result;
	}

	Vector2D Vector2D::operator+(const Vector2D & _vector)
	{
		Vector2D result;

		result.x = x + _vector.x;
		result.y = y + _vector.y;

		return result;
	}

	Vector2D Vector2D::operator*(const Vector2D & _vector)
	{
		Vector2D result;

		result.x = x * _vector.x;
		result.y = y * _vector.y;

		return result;
	}

	void Vector2D::operator+=(const Vector2D & _vector)
	{
		x += _vector.x;
		y += _vector.y;
	}

	void Vector2D::operator-=(const Vector2D & _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
	}

	Vector2D Vector2D::operator/(const float & _value)
	{
		return Vector2D(x / _value, y / _value);
	}

	void Vector2D::operator/=(const float & _value)
	{
		x /= _value;
		y /= _value;
	}

	bool Vector2D::operator==(const Vector2D & _vector)
	{
		if (x != _vector.x)
			return false;
		if (y != _vector.y)
			return false;

		return true;
	}

	bool Vector2D::operator!=(const Vector2D & _vector)
	{
		if (x != _vector.x)
			return true;
		if (y != _vector.y)
			return true;

		return false;
	}

	Vector2D Vector2D::operator*(const float & _value)
	{
		return Vector2D(x * _value, y * _value);
	}

	void Vector2D::operator*=(const float & _value)
	{
		x *= _value;
		y *= _value;
	}

	float & Vector2D::operator[](const int idx)
	{
		return (&x)[idx];
	}

	float Vector2D::dot(const Vector2D & _vector)
	{
		return (x * _vector.x) + (y * _vector.y);	
	}

	float Vector2D::length()
	{
		return math::Sqrt(math::Square(x) + math::Square(y));
	}

	float Vector2D::lengthSquared()
	{
		return math::Square(x) + math::Square(y);
	}

	void Vector2D::normalize()
	{
		float length = this->length();

		if (length != 0)
		{
			x /= length, y /= length;
		}
	}

	void Vector2D::escalate(float _scalar)
	{
		normalize();
		*this *= _scalar;
	}

	void Vector2D::truncate(float _max)
	{
		float mag = this->length();

		if (mag > _max)
			escalate(_max);
	}

	void Vector2D::clear()
	{
		x = 0.f;
		y = 0.f;
	}
}
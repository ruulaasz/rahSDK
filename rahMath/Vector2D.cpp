#include "Vector2D.h"

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
}
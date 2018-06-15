#include "Color.h"

namespace rah
{
	rah::Color::Color(float _r, float _g, float _b, float _alpha)
	{
		r = _r;
		g = _g;
		b = _b;
		alpha = _alpha;
	}

	Color::~Color()
	{

	}

	void Color::operator=(const Color & _Color)
	{
		r = _Color.r;
		g = _Color.g;
		b = _Color.b;
		alpha = _Color.alpha;
	}

	Color Color::operator+(const Color & _Color)
	{
		return Color(r+_Color.r, g + _Color.g, b + _Color.b, alpha + _Color.alpha);
	}
	Color Color::operator-(const Color & _Color)
	{
		return Color(r - _Color.r, g - _Color.g, b - _Color.b, alpha - _Color.alpha);
	}
	void Color::operator+=(const Color & _Color)
	{
		r += _Color.r;
		g += _Color.g;
		b += _Color.b;
		alpha += _Color.alpha;
	}

	void Color::operator-=(const Color & _Color)
	{
		r -= _Color.r;
		g -= _Color.g;
		b -= _Color.b;
		alpha -= _Color.alpha;
	}

	bool Color::operator==(const Color & _Color)
	{
		if (r != _Color.r)
			return false;
		if (g != _Color.g)
			return false;
		if (b != _Color.b)
			return false;
		if (alpha != _Color.alpha)
			return false;

		return true;
	}

	bool Color::operator!=(const Color & _Color)
	{
		if (r != _Color.r)
			return true;
		if (g != _Color.g)
			return true;
		if (b != _Color.b)
			return true;
		if (alpha != _Color.alpha)
			return true;

		return false;
	}

	void Color::clear()
	{
		r = 0.f;
		g = 0.f;
		b = 0.f;
		alpha = 1.f;
	}
}
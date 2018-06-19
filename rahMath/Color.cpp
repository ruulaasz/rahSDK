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
		Color r(r+_Color.r, g + _Color.g, b + _Color.b, alpha + _Color.alpha);

		if (r.r > 1.f)
			r.r = 1.f;

		if (r.g > 1.f)
			r.g = 1.f;

		if (r.b > 1.f)
			r.b = 1.f;

		if (r.alpha > 1.f)
			r.alpha = 1.f;

		return r;
	}

	Color Color::operator-(const Color & _Color)
	{
		Color r(r - _Color.r, g - _Color.g, b - _Color.b, alpha - _Color.alpha);

		if (r.r < 0.f)
			r.r = 0.f;

		if (r.g < 0.f)
			r.g = 0.f;

		if (r.b < 0.f)
			r.b = 0.f;

		if (r.alpha < 0.f)
			r.alpha = 0.f;

		return r;
	}

	void Color::operator+=(const Color & _Color)
	{
		r += _Color.r;
		g += _Color.g;
		b += _Color.b;
		alpha += _Color.alpha;

		if (r > 1.f)
			r = 1.f;

		if (g > 1.f)
			g = 1.f;

		if (b > 1.f)
			b = 1.f;

		if (alpha > 1.f)
			alpha = 1.f;
	}

	void Color::operator-=(const Color & _Color)
	{
		r -= _Color.r;
		g -= _Color.g;
		b -= _Color.b;
		alpha -= _Color.alpha;

		if (r < 0.f)
			r = 0.f;

		if (g < 0.f)
			g = 0.f;

		if (b < 0.f)
			b = 0.f;

		if (alpha < 0.f)
			alpha = 0.f;
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
#include "Color.h"

namespace rah
{
	Color rah::Color::black = Color();
	Color rah::Color::white = Color(1.f, 1.f, 1.f);
	Color rah::Color::red = Color(1.f);
	Color rah::Color::green = Color(0.f, 1.f);
	Color rah::Color::blue = Color(0.f, 0.f, 1.f);

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

	void Color::operator=(const Vector4D & _vec)
	{
		r = _vec.x;
		g = _vec.y;
		b = _vec.z;
		alpha = _vec.w;
	}

	Color Color::operator+(const Color & _Color)
	{
		Color color(r+_Color.r, g + _Color.g, b + _Color.b, alpha + _Color.alpha);

		if (color.r > 1.f)
			color.r = 1.f;

		if (color.g > 1.f)
			color.g = 1.f;

		if (color.b > 1.f)
			color.b = 1.f;

		if (color.alpha > 1.f)
			color.alpha = 1.f;

		return color;
	}

	Color Color::operator-(const Color & _Color)
	{
		Color color(r - _Color.r, g - _Color.g, b - _Color.b, alpha - _Color.alpha);

		if (color.r < 0.f)
			color.r = 0.f;

		if (color.g < 0.f)
			color.g = 0.f;

		if (color.b < 0.f)
			color.b = 0.f;

		if (color.alpha < 0.f)
			color.alpha = 0.f;

		return color;
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
		alpha = 0.f;
	}
}
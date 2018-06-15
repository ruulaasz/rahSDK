#include "Degrees.h"
#include "Radians.h"
#include "rahMath.h"

namespace rah
{
	Degrees::Degrees(float _value)
	{
		m_degrees = _value;
	}

	Degrees::Degrees(const Degrees & _degrees)
	{
		m_degrees = _degrees.m_degrees;
	}

	Degrees::Degrees(const Radians & _radians)
	{
		m_degrees = _radians.m_radians * math::RAD_TO_DEG;
	}

	Degrees::~Degrees()
	{

	}

	void Degrees::operator=(const Degrees & _degrees)
	{
		m_degrees = _degrees.m_degrees;
	}

	void Degrees::operator=(const Radians & _radians)
	{
		m_degrees = _radians.m_radians * math::RAD_TO_DEG;
	}

	Degrees Degrees::operator+(const Degrees & _degrees)
	{
		return Degrees(m_degrees + _degrees.m_degrees);
	}

	Degrees Degrees::operator+(const Radians & _radians)
	{
		return Degrees(m_degrees + _radians.m_radians * math::RAD_TO_DEG);
	}

	Degrees Degrees::operator-(const Degrees & _degrees)
	{
		return Degrees(m_degrees - _degrees.m_degrees);
	}

	Degrees Degrees::operator-(const Radians & _radians)
	{
		return Degrees(m_degrees - _radians.m_radians * math::RAD_TO_DEG);
	}

	void Degrees::operator+=(const Degrees & _degrees)
	{
		m_degrees += _degrees.m_degrees;
	}

	void Degrees::operator+=(const Radians & _radians)
	{
		m_degrees += _radians.m_radians * math::RAD_TO_DEG;
	}

	void Degrees::operator-=(const Degrees & _degrees)
	{
		m_degrees -= _degrees.m_degrees;
	}

	void Degrees::operator-=(const Radians & _radians)
	{
		m_degrees -= _radians.m_radians * math::RAD_TO_DEG;
	}

	float Degrees::getRadians()
	{
		return m_degrees * math::DEG_TO_RAD;
	}
}
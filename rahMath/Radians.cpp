#include "Radians.h"
#include "Degrees.h"
#include "rahMath.h"

namespace rah
{
	Radians::Radians(float _value)
	{
		m_radians = _value;
	}

	Radians::Radians(const Radians & _radians)
	{
		m_radians = _radians.m_radians;
	}

	Radians::Radians(const Degrees & _degrees)
	{
		m_radians = _degrees.m_degrees * math::DEG_TO_RAD;
	}

	Radians::~Radians()
	{

	}

	void Radians::operator=(const Degrees & _degrees)
	{
		m_radians = _degrees.m_degrees * math::DEG_TO_RAD;
	}

	void Radians::operator=(const Radians & _radians)
	{
		m_radians = _radians.m_radians;
	}

	Radians Radians::operator+(const Degrees & _degrees)
	{
		return Radians(m_radians+(_degrees.m_degrees * math::DEG_TO_RAD));
	}

	Radians Radians::operator+(const Radians & _radians)
	{
		return Radians(m_radians + _radians.m_radians);
	}

	Radians Radians::operator-(const Degrees & _degrees)
	{
		return Radians(m_radians - (_degrees.m_degrees * math::DEG_TO_RAD));
	}

	Radians Radians::operator-(const Radians & _radians)
	{
		return Radians(m_radians - _radians.m_radians);
	}

	void Radians::operator+=(const Degrees & _degrees)
	{
		m_radians += (_degrees.m_degrees * math::DEG_TO_RAD);
	}

	void Radians::operator+=(const Radians & _radians)
	{
		m_radians += _radians.m_radians;
	}

	void Radians::operator-=(const Degrees & _degrees)
	{
		m_radians -= (_degrees.m_degrees * math::DEG_TO_RAD);
	}

	void Radians::operator-=(const Radians & _radians)
	{
		m_radians -= _radians.m_radians;
	}

	float Radians::getDegrees()
	{
		return m_radians * math::RAD_TO_DEG;
	}
}
#include "Plane.h"

namespace rah
{
	Plane::Plane()
	{

	}

	Plane::Plane(Vector3D _Normal, Vector3D _Point)
	{
		m_normal = _Normal;
		m_point = _Point;
		m_length = m_point.length();
	}

	Plane::Plane(const Plane & _plane)
	{
		m_normal = _plane.m_normal;
		m_point = _plane.m_point;
		m_length = _plane.m_length;
	}

	Plane::~Plane()
	{

	}
}
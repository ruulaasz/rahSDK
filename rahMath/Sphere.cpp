#include "Sphere.h"

namespace rah
{
	Sphere::Sphere()
	{

	}

	rah::Sphere::Sphere(float _radius, Vector3D _center)
	{
		m_radius = _radius;
		m_center = _center;
	}

	Sphere::Sphere(const Sphere & _sphere)
	{
		m_center = _sphere.m_center;
		m_radius = _sphere.m_radius;
	}

	Sphere::~Sphere()
	{

	}
}
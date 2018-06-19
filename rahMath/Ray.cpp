#include "Ray.h"

namespace rah
{
	Ray::Ray()
	{

	}

	rah::Ray::Ray(Vector3D _origin, Vector3D _direction)
	{
		m_origin = _origin;
		m_direction = _direction;
	}

	rah::Ray::Ray(const Ray & _ray)
	{
		m_origin = _ray.m_origin;
		m_direction = _ray.m_direction;
	}

	Ray::~Ray()
	{

	}
}
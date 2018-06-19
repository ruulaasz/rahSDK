#pragma once
#include "Vector3D.h"

namespace rah
{
	/**
	* A Geometric Ray
	*
	*/
	class Ray
	{
	public:
		Ray();
		Ray(Vector3D _origin, Vector3D _direction);
		Ray(const Ray &_ray);
		virtual ~Ray();

		Vector3D m_origin;
		Vector3D m_direction;
	};
}
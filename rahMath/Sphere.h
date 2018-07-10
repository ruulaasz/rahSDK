#pragma once
#include "Vector3D.h"

namespace rah
{
	/**
	* A Geometric Sphere
	*
	*/
	class Sphere
	{
	public:
		Sphere();
		Sphere(float _radius, Vector3D _center);
		Sphere(const Sphere &_sphere);
		~Sphere();

		float m_radius;
		Vector3D m_center;
	};
}
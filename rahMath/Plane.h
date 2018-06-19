#pragma once
#include "Vector3D.h"

namespace rah
{
	/**
	* A Geometric Plane
	*
	*/
	class Plane
	{
	public:
		Plane();
		Plane(Vector3D _Normal, Vector3D _Point);
		Plane(const Plane& _plane);
		virtual ~Plane();

		Vector3D m_normal;			
		Vector3D m_point;			
		float m_length;
	};
}
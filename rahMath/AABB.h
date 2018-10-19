#pragma once
#include "Vector3D.h"
namespace rah
{
	class AABB
	{
	public:
		Vector3D m_center;
		Vector3D m_min;
		Vector3D m_max;
		AABB();
		AABB(Vector3D _center, Vector3D _min, Vector3D _max);
		~AABB();
	};
}


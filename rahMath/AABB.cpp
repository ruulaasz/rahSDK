#include "AABB.h"


namespace rah
{
	AABB::AABB()
	{
	}

	AABB::AABB(Vector3D _center, Vector3D _min, Vector3D _max)
	{
		m_center = _center;
		m_min = _min;
		m_max = _max;
	}


	AABB::~AABB()
	{
	}
}
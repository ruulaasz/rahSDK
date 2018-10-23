#include "AABB.h"

namespace rah
{
	AABB::AABB()
	{

	}

	AABB::AABB(Vector4D _center, Vector4D _min, Vector4D _max)
	{
		m_center = _center;
		m_min = _min;
		m_max = _max;
	}

	AABB::~AABB()
	{

	}
}
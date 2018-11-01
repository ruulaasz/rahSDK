#include "AABB.h"

namespace rah
{
	AABB::AABB()
	{

	}

	AABB::AABB(Vector4D _center, Vector4D _min, Vector4D _max)
	{
		m_center = _center;
		m_center.w = 1.f;
		m_min = _min;
		m_min.w = 1.f;
		m_max = _max;
		m_max.w = 1.f;
	}

	AABB::~AABB()
	{

	}
}
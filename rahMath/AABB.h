#pragma once

#include "Vector3D.h"
#include "Vector4D.h"

namespace rah
{
	class AABB
	{
	public:
		Vector4D m_center;
		Vector4D m_min;
		Vector4D m_max;
		AABB();
		AABB(Vector4D _center, Vector4D _min, Vector4D _max);
		~AABB();
	};
}


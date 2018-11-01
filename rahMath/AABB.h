#pragma once

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3D.h"

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
		void RotateAABB(Matrix3D _m);
		~AABB();
	};
}


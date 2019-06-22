#include "AABB.h"

namespace rah
{
	AABB::AABB()
	{
		m_center = Vector4D();
		m_min = Vector4D(-1.f, -1.f, -1.f, 1.f);
		m_max = Vector4D(1.f, 1.f, 1.f, 1.f);
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

	void AABB::RotateAABB(Matrix3D _m)
	{
		AABB b;
		for (int i = 0; i < 3; i++)
		{
			b.m_min[i] = b.m_max[i] = 0;

			for (int j = 0; j < 3; j++)
			{
				float e = _m.Line[i][j] * m_min[j];
				float f = _m.Line[i][j] * m_max[j];
				if (e < f) {
					b.m_min[i] += e;
					b.m_max[i] += f;
				}
				else {
					b.m_min[i] += f;
					b.m_max[i] += e;
				}
			}
		}
		m_min = b.m_min;
		m_max = b.m_max;
	}

	AABB::~AABB()
	{

	}
}
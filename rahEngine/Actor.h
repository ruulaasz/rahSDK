#pragma once

#include <rahMath.h>

namespace rah
{
	class Actor
	{
	public:
		Actor();
		~Actor();

		int m_id;
		Vector3D m_position;
	};
}
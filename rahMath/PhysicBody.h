#pragma once
#include <dynamics/q3Body.h>
#include <collision/q3Box.h>
#include "AABB.h"
#include "OBB.h"
#include "Transform.h"
namespace rah
{
	class PhysicBody
	{
	public:
		PhysicBody();
		~PhysicBody();

		void AddBox(q3BoxDef _boxDef);
		void SetTransform(Transform _transform);

		AABB GetAABB();
		OBB GetOBB();

		q3Body* m_body;
		const q3Box* m_box;
	};
}

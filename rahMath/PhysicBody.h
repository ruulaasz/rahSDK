#pragma once
#include <dynamics/q3Body.h>
#include <collision/q3Box.h>
#include <scene/q3Scene.h>
#include "AABB.h"
#include "OBB.h"
#include "Transform.h"
#include "Color.h"
namespace rah
{
	class PhysicBody : public q3QueryCallback
	{
	public:
		PhysicBody();
		~PhysicBody();

		void AddBox(q3BoxDef _boxDef);
		void ModifyBox(q3BoxDef _boxDef, const q3Box* _box);
		void SetTransform(Transform _transform);
		void SetLinearVelocity(Vector3D _direction);
		void ApplyLinearImpulseAtWorldPoint(Vector3D _direction, Vector3D _from);
		bool CanCollide(const PhysicBody *_other);
		AABB GetAABB();
		OBB GetOBB();

		bool ReportShape(q3Box *_box);

		q3Body* m_body;
		const q3Box* m_box;
		Color m_color;
	};
}

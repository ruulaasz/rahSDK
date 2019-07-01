#include "PhysicBody.h"


namespace rah
{
	PhysicBody::PhysicBody()
	{
	}


	PhysicBody::~PhysicBody()
	{
	}
	void PhysicBody::AddBox(q3BoxDef _boxDef)
	{
		m_box = m_body->AddBox(_boxDef);
	}
	void PhysicBody::SetTransform(Transform _transform)
	{
		m_body->SetTransform(q3Vec3(_transform.m_position.x, _transform.m_position.y, _transform.m_position.z));
	}
	AABB PhysicBody::GetAABB()
	{
		AABB aabb;
		aabb.m_center.x = m_body->GetTransform().position.x;
		aabb.m_center.y = m_body->GetTransform().position.y;
		aabb.m_center.z = m_body->GetTransform().position.z;

		aabb.m_max.x = m_box->e.x;
		aabb.m_max.y = m_box->e.y;
		aabb.m_max.z = m_box->e.z;

		aabb.m_min.x = -m_box->e.x;
		aabb.m_min.y = -m_box->e.y;
		aabb.m_min.z = -m_box->e.z;

		return aabb;
	}
	OBB PhysicBody::GetOBB()
	{
		OBB obb;
		obb.m_position.x = m_body->GetTransform().position.x;
		obb.m_position.y = m_body->GetTransform().position.y;
		obb.m_position.z = m_body->GetTransform().position.z;

		obb.m_dimentions.x = m_box->e.x;
		obb.m_dimentions.y = m_box->e.y;
		obb.m_dimentions.z = m_box->e.z;

		obb.m_axis[0].x = m_body->GetTransform().rotation.ex.x;
		obb.m_axis[0].y = m_body->GetTransform().rotation.ex.y;
		obb.m_axis[0].z = m_body->GetTransform().rotation.ex.z;

		obb.m_axis[1].x = m_body->GetTransform().rotation.ey.x;
		obb.m_axis[1].y = m_body->GetTransform().rotation.ey.y;
		obb.m_axis[1].z = m_body->GetTransform().rotation.ey.z;

		obb.m_axis[2].x = m_body->GetTransform().rotation.ez.x;
		obb.m_axis[2].y = m_body->GetTransform().rotation.ez.y;
		obb.m_axis[2].z = m_body->GetTransform().rotation.ez.z;

		return obb;
	}
}
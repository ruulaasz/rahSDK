#include "BoxComponent.h"
#include "rahEngine.h"

namespace rah
{
	BoxComponent::BoxComponent()
	{
		m_rendereable = true;
		m_color = Color::blue;
	}

	BoxComponent::~BoxComponent()
	{

	}

	void BoxComponent::init()
	{
		adjustBox();

		Transform t = m_owner->m_transform;

		Matrix3D rot;

		rot = rah::math::RotationMatrix3x3(rah::Degrees(t.m_rotation.x).getRadians(), rah::math::Axis_X);
		rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(t.m_rotation.y).getRadians(), rah::math::Axis_Y);
		rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(t.m_rotation.z).getRadians(), rah::math::Axis_Z);

		m_box.RotateAABB(rot);

		m_box.m_min.x *= t.m_scale.x;
		m_box.m_max.x *= t.m_scale.x;

		m_box.m_min.y *= t.m_scale.y;
		m_box.m_max.y *= t.m_scale.y;

		m_box.m_min.z *= t.m_scale.z;
		m_box.m_max.z *= t.m_scale.z;
	}

	void BoxComponent::render()
	{
		if (m_rendereable)
		{
			RenderManager::GetInstance().renderShape(m_box, m_color);
		}


	}

	void BoxComponent::update(float /*_deltaTime*/)
	{
		adjustBox();
		
		Transform t = m_owner->m_transform;

		m_box.m_center = t.m_position;
		m_box.m_center = t.m_position;

		m_box.m_min.x *= t.m_scale.x;
		m_box.m_max.x *= t.m_scale.x;

		m_box.m_min.y *= t.m_scale.y;
		m_box.m_max.y *= t.m_scale.y;

		m_box.m_min.z *= t.m_scale.z;
		m_box.m_max.z *= t.m_scale.z;

		Matrix3D rot;

		rot = rah::math::RotationMatrix3x3(rah::Degrees(t.m_rotation.x).getRadians(), rah::math::Axis_X);
		rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(t.m_rotation.y).getRadians(), rah::math::Axis_Y);
		rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(t.m_rotation.z).getRadians(), rah::math::Axis_Z);

		m_box.RotateAABB(rot);
	}

	void BoxComponent::addModel(Model * _model)
	{
		m_model = _model;
	}

	void BoxComponent::adjustBox()
	{
		if (m_model != NULL)
		{
			m_box = m_model->getBox();
		}
		else
		{
			m_box = AABB(m_owner->m_transform.m_position, Vector4D(-2, -2, -2, 1), Vector4D(2, 2, 2, 1));
		}
	}
}
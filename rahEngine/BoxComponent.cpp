#include "BoxComponent.h"
#include "rahEngine.h"

namespace rah
{
	BoxComponent::BoxComponent()
	{
		m_rendereable = true;
		m_adjustToModel = true;
		m_color = Color::blue;
	}

	BoxComponent::~BoxComponent()
	{

	}

	void BoxComponent::init(Actor* _owner, void* _data)
	{
		m_owner = _owner;
	}

	void BoxComponent::render()
	{
		ImgManager::GetInstance().boxComponentGUI(this);

		if (m_rendereable)
		{
			RenderManager::GetInstance().renderShape(m_box, m_color);
		}
	}

	void BoxComponent::update(float /*_deltaTime*/)
	{
		if (m_adjustToModel)
		{
			if (m_owner->m_transform != m_lastTransform)
			{
				adjustBoxtoModel();
			}
		}
		else
		{
			Transform t = m_owner->m_transform;
			Matrix3D rot;
			m_box = AABB();

			m_box.m_center = m_owner->m_transform.m_position + m_offsetTransform.m_position;

			rot = rah::math::RotationMatrix3x3(rah::Degrees(m_offsetTransform.m_rotation.x).getRadians(), rah::math::Axis_X);
			rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(m_offsetTransform.m_rotation.y).getRadians(), rah::math::Axis_Y);
			rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(m_offsetTransform.m_rotation.z).getRadians(), rah::math::Axis_Z);

			m_box.RotateAABB(rot);

			m_box.m_min.x *= m_offsetTransform.m_scale.x;
			m_box.m_max.x *= m_offsetTransform.m_scale.x;

			m_box.m_min.y *= m_offsetTransform.m_scale.y;
			m_box.m_max.y *= m_offsetTransform.m_scale.y;

			m_box.m_min.z *= m_offsetTransform.m_scale.z;
			m_box.m_max.z *= m_offsetTransform.m_scale.z;
		}
	}

	void BoxComponent::adjustBoxtoModel()
	{
		Matrix3D rot;
		Transform t = m_owner->m_transform;

		if (m_model != NULL)
		{
			m_box = m_model->getBox();

			m_box.m_center = m_owner->m_transform.m_position;

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

			m_lastTransform = m_owner->m_transform;
		}
	}

	void BoxComponent::assignModel(Model * _model)
	{
		m_model = _model;

		adjustBoxtoModel();
	}
}
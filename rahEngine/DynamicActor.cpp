#include "DynamicActor.h"


namespace rah
{
	RahResult DynamicActor::Initialize(void * _initData)
	{
		SimpleActorInit* actorData = (SimpleActorInit*)_initData;
		m_color = actorData->_color;
		m_transform = actorData->_transform;
		m_LastTransform = m_transform;

		rah::BasicResourceParams* rParams = new rah::BasicResourceParams();
		rParams->filePath = actorData->_nameModel;
		m_model = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(rParams, rah::ResourceTypes::RAH_Model);

		if (m_model == NULL)
			return rah::ResourceManager::GetInstance().GetLastError();

		m_box = m_model->getBox();

		m_box.m_center = m_transform.m_position;

		Matrix3D rot;
	
		rot = rah::math::RotationMatrix3x3(rah::Degrees(m_transform.m_rotation.x).getRadians(), rah::math::Axis_X);
		rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(m_transform.m_rotation.y).getRadians(), rah::math::Axis_Y);
		rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(m_transform.m_rotation.z).getRadians(), rah::math::Axis_Z);

		m_box.RotateAABB(rot);

		m_box.m_min.x *= m_transform.m_scale.x;
		m_box.m_max.x *= m_transform.m_scale.x;

		m_box.m_min.y *= m_transform.m_scale.y;
		m_box.m_max.y *= m_transform.m_scale.y;

		m_box.m_min.z *= m_transform.m_scale.z;
		m_box.m_max.z *= m_transform.m_scale.z;

		RAH_SAFE_DELETE(rParams);
		return RAH_SUCCESS;
	}
	void DynamicActor::Update(float _deltaTime)
	{
		if (m_transform.m_position != m_LastTransform.m_position)
		{
			m_LastTransform.m_position = m_transform.m_position;
			m_box.m_center = m_transform.m_position;
		}

		if (m_transform.m_scale != m_LastTransform.m_scale)
		{
			m_box = m_model->getBox();

			m_box.m_center = m_transform.m_position;

			m_LastTransform.m_scale = m_transform.m_scale;

			m_box.m_min.x *= m_transform.m_scale.x;
			m_box.m_max.x *= m_transform.m_scale.x;

			m_box.m_min.y *= m_transform.m_scale.y;
			m_box.m_max.y *= m_transform.m_scale.y;

			m_box.m_min.z *= m_transform.m_scale.z;
			m_box.m_max.z *= m_transform.m_scale.z;
		}

		if (m_transform.m_rotation != m_LastTransform.m_rotation)
		{
			m_LastTransform.m_rotation = m_transform.m_rotation;

			Matrix3D rot;

			rot = rah::math::RotationMatrix3x3(rah::Degrees(m_transform.m_rotation.x).getRadians(), rah::math::Axis_X);
			rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(m_transform.m_rotation.y).getRadians(), rah::math::Axis_Y);
			rot = rot * rah::math::RotationMatrix3x3(rah::Degrees(m_transform.m_rotation.z).getRadians(), rah::math::Axis_Z);

			m_box.RotateAABB(rot);
		}
		
	}
	void DynamicActor::Render()
	{
		rah::RenderManager::GetInstance().updateWorld(m_transform.TransformToWorldMatrix());
		rah::RenderManager::GetInstance().updateColor(m_color);
		m_model->render();
		RenderManager::GetInstance().renderShape(m_box, Color::blue);
	}
	void DynamicActor::Destroy()
	{
		m_color.clear();
		m_transform = Transform(0);
		m_model->Destroy();
	}
	DynamicActor::DynamicActor()
	{
	}


	DynamicActor::~DynamicActor()
	{
	}
}
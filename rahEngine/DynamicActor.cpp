#include "DynamicActor.h"
#include "Component.h"

namespace rah
{
	RahResult DynamicActor::Initialize(void * _initData)
	{
		SimpleActorInit* actorData = (SimpleActorInit*)_initData;
		m_transform = actorData->_transform;
		m_LastTransform = m_transform;

		return RAH_SUCCESS;
	}

	void DynamicActor::Update(float _deltaTime)
	{
		__super::Update(_deltaTime);

		if (m_transform != m_LastTransform)
		{
			m_LastTransform = m_transform;
		}
	}

	void DynamicActor::Render()
	{
		rah::RenderManager::GetInstance().updateWorld(m_transform.TransformToWorldMatrix());

		__super::Render();
	}

	void DynamicActor::Destroy()
	{
		m_transform = Transform(0);
	}

	DynamicActor::DynamicActor()
	{

	}

	DynamicActor::~DynamicActor()
	{

	}
}
#include "DynamicActor.h"


namespace rah
{
	RahResult DynamicActor::Initialize(void * _initData)
	{
		SimpleActorInit* actorData = (SimpleActorInit*)_initData;
		m_color = actorData->_color;
		m_transform = actorData->_transform;

		rah::BasicResourceParams* rParams = new rah::BasicResourceParams();
		rParams->filePath = actorData->_nameModel;
		m_model = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(rParams, rah::ResourceTypes::RAH_Model);

		if (m_model == NULL)
			return rah::ResourceManager::GetInstance().GetLastError();

		RAH_SAFE_DELETE(rParams);
		return RAH_SUCCESS;
	}
	void DynamicActor::Update(float _deltaTime)
	{
	}
	void DynamicActor::Render()
	{
	}
	void DynamicActor::Destroy()
	{
		m_color; // ponerlo blanco
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
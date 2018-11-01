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

		m_box = m_model->getBox();
		m_box.m_center = m_transform.m_position;
		RAH_SAFE_DELETE(rParams);
		return RAH_SUCCESS;
	}
	void DynamicActor::Update(float _deltaTime)
	{
	}
	void DynamicActor::Render()
	{
		rah::RenderManager::GetInstance().updateWorld(m_transform.TransformToWorldMatrix());
		rah::RenderManager::GetInstance().updateColor(m_color);
		m_model->render();
		RenderManager::GetInstance().renderShape(m_box, Color(0,0,1));
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
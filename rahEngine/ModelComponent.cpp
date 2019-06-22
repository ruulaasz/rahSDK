#include "ModelComponent.h"
#include "rahAll.h"
#include "Actor.h"

namespace rah
{
	ModelComponent::ModelComponent()
	{

	}

	ModelComponent::~ModelComponent()
	{

	}

	void ModelComponent::init()
	{
		m_color = Color(0.f, 0.f, 0.f, 1.f);

		rah::BasicResourceParams* rParams = new rah::BasicResourceParams();
		rParams->filePath = "resources\\models\\ManEater\\ManEater.dae";

		m_model = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(rParams, rah::ResourceTypes::RAH_Model);
	}

	void ModelComponent::render()
	{
		rah::RenderManager::GetInstance().updateWorld(m_owner->m_transform.TransformToWorldMatrix());
		RenderManager::GetInstance().updateColor(m_color);
		m_model->render();
	}

	void ModelComponent::update(float /*_deltaTime*/)
	{
		m_model->m_transform = m_owner->m_transform.TransformToWorldMatrix();
	}
}
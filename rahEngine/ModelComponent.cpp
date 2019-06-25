#include "ModelComponent.h"
#include "rahAll.h"
#include "rahEngine.h"

namespace rah
{
	ModelComponent::ModelComponent()
	{

	}

	ModelComponent::~ModelComponent()
	{

	}

	void ModelComponent::init(Actor* _owner, void* _data)
	{
		m_owner = _owner;
		m_color = Color(0.f, 0.f, 0.f, 1.f);

		rah::BasicResourceParams* rParams = new rah::BasicResourceParams();
		rParams->filePath = "resources\\models\\ManEater\\ManEater.dae";

		m_model = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(rParams, rah::ResourceTypes::RAH_Model);
	}

	void ModelComponent::render()
	{
		ImgManager::GetInstance().modelComponentGUI(this);

		if (m_rendereable)
		{
			rah::RenderManager::GetInstance().updateWorld(m_owner->m_transform.TransformToWorldMatrix());
			RenderManager::GetInstance().updateColor(m_color);
			m_model->render();
		}
	}

	void ModelComponent::update(float /*_deltaTime*/)
	{
		m_model->m_transform = m_owner->m_transform.TransformToWorldMatrix();
	}

	void ModelComponent::changeModel(std::string _path)
	{
		rah::BasicResourceParams params;
		params.filePath = _path;

		m_model = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(&params, rah::ResourceTypes::RAH_Model);
	}
}
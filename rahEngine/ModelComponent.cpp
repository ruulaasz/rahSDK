#include "ModelComponent.h"

namespace rah
{
	ModelComponent::ModelComponent()
	{

	}

	ModelComponent::~ModelComponent()
	{

	}

	void ModelComponent::render()
	{
		m_model->render();
	}

	void ModelComponent::update(float _deltaTime)
	{
		_deltaTime;
	}
}
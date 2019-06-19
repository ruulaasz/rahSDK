#include "ComponentManager.h"
#include "Component.h"

namespace rah
{
	ComponentManager::ComponentManager()
	{

	}

	ComponentManager::~ComponentManager()
	{

	}

	RahResult ComponentManager::Initialize(void * _init)
	{
		_init;
		return RahResult();
	}

	void ComponentManager::Release()
	{

	}

	void ComponentManager::render()
	{
		for (const auto& n : m_Components) 
		{
			n.second->render();
		}
	}

	void ComponentManager::update(float _deltaTime)
	{
		for (const auto& n : m_Components)
		{
			n.second->update(_deltaTime);
		}
	}

	void ComponentManager::addComponent(Component * _component)
	{
		if (_component)
		{
			m_Components[_component->m_id] = _component;
		}
	}

	Component * ComponentManager::getComponent(std::string _componentID)
	{
		if (m_Components[_componentID])
		{
			return m_Components[_componentID];
		}
		else
			return nullptr;
	}
}
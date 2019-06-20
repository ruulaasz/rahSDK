#include "Actor.h"
#include "Component.h"

namespace rah
{
	size_t rah::Actor::m_autoID = 1;

	void Actor::Update(float _deltaTime)
	{
		for (auto& it : m_Components)
		{
			if (it.second != NULL)
				it.second->update(_deltaTime);
		}
	}

	void Actor::Render()
	{
		for (auto& it : m_Components)
		{
			if(it.second != NULL)
				it.second->render();
		}
	}

	RahResult Actor::addComponent(Component * _component)
	{
		if (_component)
		{
			auto model = m_Components.find(_component->m_id);

			if (model != m_Components.end())
			{
				return RAH_ERROR;
			}
			else
			{
				_component->init();
				m_Components[_component->m_id] = _component;
				m_componentNumber++;
				return RAH_SUCCESS;
			}
		}

		return RAH_ERROR;
	}

	void Actor::removeComponent(std::string _id)
	{
		for (auto it = m_Components.begin(); it != m_Components.end(); )
		{
			if (it->first == _id)
			{
				it = m_Components.erase(it);
				m_componentNumber--;
				return;
			}
			else
			{
				++it;
			}
		}
	}

	Actor::Actor()
	{
		m_id = m_autoID;
		m_autoID++;
	}

	Actor::~Actor()
	{

	}
}
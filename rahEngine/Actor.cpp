#include "Actor.h"
#include "Component.h"

namespace rah
{
	size_t rah::Actor::m_autoID = 1;

	void Actor::Update(float _deltaTime)
	{
		for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
		{
			it->second->update(_deltaTime);
		}
	}

	void Actor::Render()
	{
		for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
		{
			it->second->render();
		}
	}

	void Actor::addComponent(Component * _component)
	{
		if (_component)
		{
			m_Components[_component->m_id] = _component;
		}
	}

	void Actor::removeComponent(std::string m_id)
	{
		for (auto it = m_Components.begin(); it != m_Components.end(); )
		{
			if (it->first == m_id)
			{
				it = m_Components.erase(it);
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
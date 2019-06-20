#include "World.h"

namespace rah
{
	RahResult World::Initialize()
	{
		return RAH_SUCCESS;
	}

	void World::Update(float _deltaTime)
	{
		for (size_t i = 0; i < m_actors.size(); i++)
		{
			m_actors[i]->Update(_deltaTime);
		}
	}

	void World::Render()
	{
		for (size_t i = 0; i < m_actors.size(); i++)
		{
			m_actors[i]->Render();
		}
	}

	void World::Destroy()
	{
		for (size_t i = 0; i < m_actors.size(); i++)
		{
			m_actors[i]->Destroy();
			RAH_SAFE_DELETE(m_actors[i]);
		}
		m_actors.clear();
	}

	RahResult World::RegisterActor(Actor * _actor)
	{
		if (_actor == NULL)
			return RAH_PARAM_IS_NULL;

		m_actors.push_back(_actor);

		return RAH_SUCCESS;
	}

	World::World()
	{

	}

	World::~World()
	{

	}
}
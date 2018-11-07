#pragma once
#include "rahAll.h"
#include "Actor.h"
#include <vector>
namespace rah
{
	class World
	{
	protected:
		std::vector<Actor*> m_actors;
	public:
		RahResult Initialize();
		void Update(float _deltaTime = 0);
		void Render();
		void Destroy();
		RahResult RegisterActor(Actor* _actor);
		World();
		~World();
	};
}

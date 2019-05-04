#pragma once
#include "rahAll.h"
#include "Actor.h"
#include <vector>
namespace rah
{
	class World
	{	
	public:
		RahResult Initialize();
		void Update(float _deltaTime = 0);
		void Render();
		void Destroy();
		RahResult RegisterActor(Actor* _actor);
		World();
		~World();

		std::vector<Actor*> m_actors;
	};
}

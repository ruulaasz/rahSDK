#pragma once
#include <rahTools.h>
#include "Vector3D.h"
#include <scene/q3Scene.h>
#include "PhysicBody.h"

namespace rah
{
	struct InitPhysic
	{
		float dt;
		Vector3D gravity;
		int iterations;
		bool paused;
	};
	class PhysicManager : public rah::Module<PhysicManager, InitPhysic>
	{
	public:
		PhysicManager();
		~PhysicManager();

		RahResult Initialize(InitPhysic _init);

		PhysicBody* CreateBody(const q3BodyDef& _def);

		void Update(float _deltaTime = 0.0f);

		void Release();

		q3Scene* m_scene;
		float m_dt;
		bool m_paused;
	};
}

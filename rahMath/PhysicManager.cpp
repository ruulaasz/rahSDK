#include "PhysicManager.h"

namespace rah
{
	PhysicManager::PhysicManager()
	{
	}


	PhysicManager::~PhysicManager()
	{
	}
	RahResult PhysicManager::Initialize(InitPhysic _init)
	{
		m_dt = _init.dt;
		m_scene = new q3Scene(m_dt, q3Vec3(_init.gravity.x, _init.gravity.y, _init.gravity.z), _init.iterations);
		m_paused = _init.paused;
		if (m_scene == NULL)
		{
			GetLastError() = RahResult::RAH_ERROR;
			return RahResult::RAH_ERROR;
		}
		GetLastError() = RahResult::RAH_SUCCESS;
		return RahResult::RAH_SUCCESS;
	}
	PhysicBody * PhysicManager::CreateBody(const q3BodyDef & _def)
	{
		PhysicBody* body = new PhysicBody();
		body->m_body = m_scene->CreateBody(_def);
		if (body->m_body == NULL)
		{
			GetLastError() = RahResult::RAH_ERROR;
		}
		GetLastError() = RahResult::RAH_SUCCESS;
		return body;
	}
	void PhysicManager::Update(float _deltaTime)
	{
		static float accumulator = 0;
		accumulator += _deltaTime;

		accumulator = q3Clamp01(accumulator);
		while (accumulator >= m_dt)
		{
			if (!m_paused)
			{
				m_scene->Step();
			}
			accumulator -= m_dt;
		}

	}
	void PhysicManager::Release()
	{
		m_scene->Shutdown();
		RAH_SAFE_DELETE(m_scene);
	}
}
#include "rahListener.h"
#include <fmod.hpp>
#include "AudioManager.h"

namespace rah
{
	int rah::rahListener::m_autoID = 0;
	rahListener::rahListener()
	{
		m_id = m_autoID;
		m_autoID++;
		m_forward = Vector3D(0.f,0.f,1.f);
		m_up = Vector3D(0.f, 1.f);
	}
	rahListener::~rahListener()
	{
	}
	void rahListener::UpdateListener(Vector3D _pos, Vector3D _vel, Vector3D _forward, Vector3D _up)
	{
		m_position = _pos;
		m_velocity = _vel;
		m_forward = _forward;
		m_up = _up;

		FMOD_VECTOR pos, vel, forward, up;
		pos = { m_position.x, m_position.y, m_position.z };
		vel = { m_velocity.x, m_velocity.y, m_velocity.z };
		forward = { m_forward.x, m_forward.y, m_forward.z };
		up = { m_up.x, m_up.y, m_up.z };
		AudioManager::GetInstance().getSystem()->set3DListenerAttributes(m_id, &pos, &vel, &forward, &up);
	}
}
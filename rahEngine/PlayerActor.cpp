#include "PlayerActor.h"
#include "ModelComponent.h"

namespace rah
{
	RahResult PlayerActor::Initialize(void * _initData)
	{
		m_velocity = Vector3D(0);
		m_timeAction = 0.5f;
		m_currentActionTime = m_timeAction;
		return __super::Initialize(_initData);
	}

	void PlayerActor::Update(float _deltaTime)
	{
		if (m_currentActionTime < m_timeAction)
		{
			if (m_direction != 0)
				m_velocity = m_direction * _deltaTime;

			m_transform.m_position += m_velocity;

			//m_direction -= m_velocity;
		}
		else
		{
			m_direction = Vector3D(0.f);
		}
		m_currentActionTime += _deltaTime;
		__super::Update(_deltaTime);
	}

	void PlayerActor::Render()
	{
		__super::Render();
	}

	void PlayerActor::Destroy()
	{
		__super::Destroy();
	}

	void PlayerActor::Move(void * _value)
	{
		MoveCommand value = *(MoveCommand*)_value;

		if (value.axis == 1)
		{
			m_direction.x += value.value;

			if (value.value < 0)
			{
				m_transform.m_rotation.y = 90;
			}
			else
			{
				m_transform.m_rotation.y = -90;
			}
		}
		else if (value.axis == 2)
		{
			m_direction.z += value.value;

			if (value.value < 0)
			{
				m_transform.m_rotation.y = 180;
			}
			else
			{
				m_transform.m_rotation.y = 0;
			}
		}
		m_currentActionTime = 0;
	}

	PlayerActor::PlayerActor()
	{
		m_movementSpeed = 0.2f;
	}

	PlayerActor::~PlayerActor()
	{

	}
}
#include "PlayerActor.h"

namespace rah
{
	RahResult PlayerActor::Initialize(void * _initData)
	{
		return __super::Initialize(_initData);
	}

	void PlayerActor::Update(float _deltaTime)
	{
		m_velocity = m_direction / _deltaTime;

		m_transform.m_position += m_velocity;

		m_direction /= _deltaTime;

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

			//m_transform.m_position.x += value.value;

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

			//m_transform.m_position.z += value.value;

			if (value.value < 0)
			{
				m_transform.m_rotation.y = 180;
			}
			else
			{
				m_transform.m_rotation.y = 0;
			}
		}
	}

	PlayerActor::PlayerActor()
	{
		m_movementSpeed = 0.2f;
	}

	PlayerActor::~PlayerActor()
	{

	}
}
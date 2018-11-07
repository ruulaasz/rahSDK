#include "PlayerActor.h"


namespace rah
{
	RahResult PlayerActor::Initialize(void * _initData)
	{
		return __super::Initialize(_initData);
	}
	void PlayerActor::Update(float _deltaTime)
	{
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
			m_transform.m_position.x += value.value;
		else if(value.axis == 2)
			m_transform.m_position.z += value.value;
	}
	PlayerActor::PlayerActor()
	{
	}
	PlayerActor::~PlayerActor()
	{
	}
}
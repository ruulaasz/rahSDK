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
	PlayerActor::PlayerActor()
	{
	}
	PlayerActor::~PlayerActor()
	{
	}
}
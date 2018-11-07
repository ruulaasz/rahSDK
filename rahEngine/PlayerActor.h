#pragma once
#include "DynamicActor.h"

namespace rah
{
	class PlayerActor : public DynamicActor
	{
	public:
		virtual RahResult Initialize(void* _initData = NULL);
		virtual void Update(float _deltaTime);
		virtual void Render();
		virtual void Destroy();
	public:
		PlayerActor();
		virtual ~PlayerActor();
	};
}

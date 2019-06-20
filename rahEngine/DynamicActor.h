#pragma once

#include "rahAll.h"
#include "Actor.h"

namespace rah
{
	struct SimpleActorInit
	{
		Transform _transform;
	};

	class DynamicActor : public Actor
	{
	protected:
		Transform m_LastTransform;

	public:
		virtual RahResult Initialize(void* _initData = NULL);
		virtual void Update(float _deltaTime);
		virtual void Render();
		virtual void Destroy();
		DynamicActor();
		virtual ~DynamicActor();
	};
}
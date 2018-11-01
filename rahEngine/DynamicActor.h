#pragma once
#include "rahAll.h"
#include "Actor.h"

namespace rah
{
	struct SimpleActorInit
	{
		Transform _transform;
		std::string _nameModel;
		Color _color;
	};
	class DynamicActor : public Actor
	{
	public:
		Model* m_model;
		AABB m_box;
		Color m_color;
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

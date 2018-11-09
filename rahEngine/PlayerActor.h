#pragma once

#include "DynamicActor.h"

namespace rah
{
	struct MoveCommand
	{
		float value;
		// 1 == x, 2 == z
		int axis;
	};

	class PlayerActor : public DynamicActor
	{
	public:
		virtual RahResult Initialize(void* _initData = NULL);
		virtual void Update(float _deltaTime);
		virtual void Render();
		virtual void Destroy();
		void Move(void* _value);

	public:
		PlayerActor();
		virtual ~PlayerActor();
		float m_movementSpeed;
		Vector3D m_velocity;
		Vector3D m_direction;
	};
}
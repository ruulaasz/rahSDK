#pragma once
#include "Component.h"
#include "rahAll.h"

namespace rah
{
	class ListenerComponent : public Component
	{
	public:
		ListenerComponent();
		~ListenerComponent();

		virtual void init(Actor* _owner, void* _data = NULL);
		virtual void update(float _deltaTime);
		virtual void render();
		void SetFowardUp(Vector3D _foward, Vector3D _up);
		void SetFoward(Vector3D _foward);
		void SetUp(Vector3D _up);

		rahListener m_listener;
		Vector3D m_lastOwnerPosition;
	};
}

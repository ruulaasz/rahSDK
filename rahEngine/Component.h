#pragma once

#include "rahAll.h"

namespace rah
{
	class Actor;

	class Component
	{
	public:
		Component();
		~Component();

		Actor* m_owner;
		std::string m_id;
		bool m_enabled;
		bool m_rendereable;

		virtual void init(Actor* _owner, void* _data = NULL) = 0;
		virtual void update(float _deltaTime) = 0;
		virtual void render() = 0;
	};
}
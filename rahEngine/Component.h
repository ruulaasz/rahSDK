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

		virtual void init() = 0;
		virtual void update(float _deltaTime) = 0;
		virtual void render() = 0;
	};
}
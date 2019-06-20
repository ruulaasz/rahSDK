#pragma once

#include "Component.h"
#include "rahAll.h"

namespace rah
{
	class BoxComponent : public Component
	{
	public:
		BoxComponent();
		~BoxComponent();

		AABB m_box;

		virtual void init();
		virtual void render();
		virtual void update(float _deltaTime);
	};
}
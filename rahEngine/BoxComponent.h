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

		virtual void init();
		virtual void render();
		virtual void update(float _deltaTime);
		virtual void addModel(Model* _model);
		void adjustBox();

		AABB m_box;
		bool m_rendereable;
		Color m_color;
		Model *m_model;
	};
}
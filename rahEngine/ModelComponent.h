#pragma once

#include "Component.h"

#include "rahAll.h"

namespace rah
{
	class ModelComponent : public Component
	{
	public:
		ModelComponent();
		~ModelComponent();

		Model* m_model;
		Color m_color;

		virtual void init();
		virtual void render();
		virtual void update(float _deltaTime);
	};
}
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

		virtual void render();
		virtual void update(float _deltaTime);
	};
}
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

		virtual void init(Actor* _owner, void* _data = NULL);
		virtual void render();
		virtual void update(float _deltaTime);
		void adjustBoxtoModel();
		void assignModel(Model* _model);

		AABB m_box;
		Color m_color;
		//bool m_rendereable;
		bool m_adjustToModel;

		Transform m_offsetTransform;
		Model *m_model;
	protected:
		Transform m_lastTransform;


	};
}
#pragma once

#include "rahAll.h"

namespace rah
{
	class Component;

	class Actor
	{
	public:
		static size_t m_autoID;
		size_t m_id;
		Transform m_transform;
		std::unordered_map<std::string, Component*> m_Components;
		size_t m_componentNumber;

		virtual RahResult Initialize(void* _initData = NULL) = 0;
		virtual void Update(float _deltaTime);
		virtual void Render();
		virtual void Destroy() = 0;

		RahResult addComponent(Component* _component);
		void removeComponent(std::string _id);

		Actor();
		virtual ~Actor();
	};
}
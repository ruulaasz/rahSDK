#pragma once

#include "rahAll.h"

namespace rah
{
	class Component;

	class ComponentManager : public Module<ComponentManager, void*>
	{
	public:
		ComponentManager();
		~ComponentManager();

		RahResult Initialize(void* _init);
		void Release();

		void render();
		void update(float _deltaTime);

		void addComponent(Component* _component);
		Component* getComponent(std::string _componentID);

		std::unordered_map<std::string, Component*> m_Components;
	};
}
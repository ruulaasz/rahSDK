#pragma once

#include "rahAll.h"

namespace rah
{
	enum ComponentTypes
	{
		CT_NONE = 0,
		CT_MODEL,
		CT_BOX,
		CT_LISTENER,
		CT_AUDIO,
		CT_TOTAL
	};

	class Component;
	class Actor;

	class ComponentFactory : public Module<ComponentFactory, void*>
	{
	public:
		static size_t m_autoID;

		ComponentFactory();
		~ComponentFactory();

		RahResult Initialize(void* _init);
		void Release();

		Component* createEmptyComponent(Actor* _owner, ComponentTypes _ct, std::string _id, void* _data = NULL);
		void setID(Component* _component, std::string _ct, std::string _id);
	};
}
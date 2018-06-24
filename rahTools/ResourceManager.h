#pragma once
#include "Module.h"
#include <string>
#include <vector>
#include "rahMacros.h"
#include "rahResource.h"
namespace rah
{
	struct ResourceManagerInit
	{
		std::string Name;
	};
	class ResourceManager : public rah::Module<ResourceManager, ResourceManagerInit>
	{
	protected:
		std::vector<rahResource*> m_resources;
	public:
		SecuredVar<std::string> m_name;
	public:
		RahResult Initialize(ResourceManagerInit _params);
		//rahResource LoadResource(BasicResourceParams _params);
	public:
		ResourceManager();
		~ResourceManager();
	};
}


#pragma once
#include "Module.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "rahMacros.h"
#include "rahResource.h"
#include "BasicResourceFabric.h"
namespace rah
{
	struct ResourceManagerInit
	{
		BasicResourceFabric* Fabric;
	};
	class ResourceManager : public rah::Module<ResourceManager, ResourceManagerInit>
	{
	protected:
		std::unordered_map<unsigned int,std::vector<rahResource*>*> m_resources;
		BasicResourceFabric* m_fabric;
	public:
		SecuredVar<std::string> m_name;
	public:
		RahResult Initialize(ResourceManagerInit _params);
		rahResource* LoadResource(BasicResourceParams _params, unsigned int _resourceType);
		void Release();
	public:
		ResourceManager();
		~ResourceManager();
	};
}


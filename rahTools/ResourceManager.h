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
		unsigned int m_automaticID;
	public:
		SecuredVar<std::string> m_name;
	public:
		RahResult Initialize(ResourceManagerInit _params);
		rahResource* LoadResource(BasicResourceParams _params, ResourceTypes _resourceType);
		rahResource* GetResourceByName(std::string _name, ResourceTypes _resourceType = RAH_DEFAULT);
		rahResource* GetResourceByFilePath(std::string _filePath, ResourceTypes _resourceType = RAH_DEFAULT);
		rahResource* GetResourceByID(int _id, ResourceTypes _resourceType = RAH_DEFAULT);
		void Release();
	public:
		ResourceManager();
		~ResourceManager();
	};
}


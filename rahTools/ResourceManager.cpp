#include "ResourceManager.h"
#include "rahMacros.h"
namespace rah 
{
	RahResult ResourceManager::Initialize(ResourceManagerInit _params)
	{
		m_name = "Resource Manager";
		m_fabric = _params.Fabric;
		for (unsigned int i = 0; i < RAH_TOTAL; i++)
		{
			m_resources[i] = new std::vector<rahResource*>;
		}
		return RAH_SUCCESS;
	}
	rahResource* ResourceManager::LoadResource(BasicResourceParams _params, unsigned int _resourceType)
	{
		rahResource* resultresourse = m_fabric->GetMemory(_resourceType);
		return resultresourse;
	}
	void ResourceManager::Release()
	{
		for (int i = RAH_TOTAL - 1; i >= 0; i--)
		{
			while (!m_resources[i]->empty())
			{
				m_resources[i]->back()->Release();
				RAH_SAFE_DELETE(m_resources[i]->back());
				m_resources[i]->pop_back();
			}
			RAH_SAFE_DELETE(m_resources[i]);
		}
	}
	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}
}

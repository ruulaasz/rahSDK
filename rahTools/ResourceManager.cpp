#include "ResourceManager.h"

namespace rah 
{
	RahResult ResourceManager::Initialize(ResourceManagerInit _params)
	{
		m_name = _params.Name;
		return RAH_SUCCESS;
	}
	/*rahResource ResourceManager::LoadResource(BasicResourceParams _params)
	{
		rahResource * resultresourse = new rahResource(_params);
		return ;
	}*/
	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}
}

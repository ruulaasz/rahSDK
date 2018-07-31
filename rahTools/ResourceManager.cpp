#include "ResourceManager.h"
#include "rahMacros.h"
#include "Debug.h"
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
		m_automaticID = 0;
		return RAH_SUCCESS;
	}
	rahResource* ResourceManager::LoadResource(BasicResourceParams* _params, ResourceTypes _resourceType)
	{
		if (_resourceType == RAH_DEFAULT || _resourceType == RAH_TOTAL)
		{
			GetLastError() = RAH_INVALID_RESOURCE_TYPE;
			std::string logtxt;
			logtxt = "Cant load resource error: " + std::to_string(RAH_INVALID_RESOURCE_TYPE) + " Resource type: " + std::to_string(_resourceType);
			RAH_SAVELOG(logtxt);
			return NULL;
		}

		if (_params->filePath.empty())
		{
			GetLastError() = RAH_FILE_PATH_EMPTY;
			std::string logtxt;
			logtxt = "File path Empty";
			RAH_SAVELOG(logtxt);
			return NULL;
		}

		std::string nameResource = rah::StringUtils::GetFileNameFromPath(_params->filePath);

		rahResource* resultresourse = GetResourceByName(nameResource, _resourceType);
		if (resultresourse != NULL)
		{
			resultresourse->m_referenceCount.Set(resultresourse->m_referenceCount.Get() + 1);
			return resultresourse;
		}

		if(_params->name.empty())
			_params->name = nameResource;
		_params->id = m_automaticID;
		m_automaticID++;
		resultresourse = m_fabric->GetMemory(_resourceType);
		RahResult resulttmp;
		resulttmp = resultresourse->Initialize(_params);
		if (resulttmp != RAH_SUCCESS)
		{
			std::string logtxt;
			logtxt = "Cant initialize resource error: " + std::to_string(resulttmp);
			RAH_SAVELOG(logtxt);
			return NULL;
		}
		resultresourse->Load();
		if (resulttmp != RAH_SUCCESS)
		{
			std::string logtxt;
			logtxt = "Cant load resource error: " + std::to_string(resulttmp);
			RAH_SAVELOG(logtxt);
			return NULL;
		}
		m_resources[_resourceType]->push_back(resultresourse);
		return resultresourse;
	}
	rahResource * ResourceManager::GetResourceByName(std::string _name, ResourceTypes _resourceType)
	{
		rahResource* returnResource = NULL;
		if (_resourceType == RAH_TOTAL)
		{
			GetLastError() = RAH_RESOURCE_TYPE_TOTAL;
			std::string logtxt;
			logtxt = "Cant get Resource type: " + std::to_string(RAH_RESOURCE_TYPE_TOTAL);
			RAH_SAVELOG(logtxt);
			return returnResource;
		}
		if (_resourceType != RAH_DEFAULT)
		{
			for (size_t i = 0; i < m_resources[_resourceType]->size(); i++)
			{
				if (m_resources[_resourceType]->at(i)->m_name.Get() == _name)
				{
					returnResource = m_resources[_resourceType]->at(i);
					return returnResource;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < RAH_TOTAL; i++)
			{
				for (size_t j = 0; j < m_resources[i]->size(); j++)
				{
					if (m_resources[i]->at(j)->m_name.Get() == _name)
					{
						returnResource = m_resources[i]->at(j);
						return returnResource;
					}
				}
			}
		}
		GetLastError() = RAH_CANT_GET_RESOURCE;
		std::string logtxt;
		logtxt = "Cant get Resource type: " + std::to_string(RAH_CANT_GET_RESOURCE);
		RAH_SAVELOG(logtxt);
		return returnResource;
	}
	rahResource * ResourceManager::GetResourceByFilePath(std::string _filePath, ResourceTypes _resourceType)
	{
		rahResource* returnResource = NULL;
		if (_resourceType == RAH_TOTAL)
		{
			GetLastError() = RAH_RESOURCE_TYPE_TOTAL;
			std::string logtxt;
			logtxt = "Cant get Resource type: " + std::to_string(RAH_RESOURCE_TYPE_TOTAL);
			RAH_SAVELOG(logtxt);
			return returnResource;
		}
		if (_resourceType != RAH_DEFAULT)
		{
			for (size_t i = 0; i < m_resources[_resourceType]->size(); i++)
			{
				if (m_resources[_resourceType]->at(i)->m_filePath.Get() == _filePath)
				{
					returnResource = m_resources[_resourceType]->at(i);
					return returnResource;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < RAH_TOTAL; i++)
			{
				for (size_t j = 0; j < m_resources[i]->size(); j++)
				{
					if (m_resources[i]->at(j)->m_filePath.Get() == _filePath)
					{
						returnResource = m_resources[i]->at(j);
						return returnResource;
					}
				}
			}
		}
		GetLastError() = RAH_CANT_GET_RESOURCE;
		std::string logtxt;
		logtxt = "Cant get Resource type: " + std::to_string(RAH_CANT_GET_RESOURCE);
		RAH_SAVELOG(logtxt);
		return returnResource;
	}
	rahResource * ResourceManager::GetResourceByID(int _id, ResourceTypes _resourceType)
	{
		rahResource* returnResource = NULL;
		if (_resourceType == RAH_TOTAL)
		{
			GetLastError() = RAH_RESOURCE_TYPE_TOTAL;
			std::string logtxt;
			logtxt = "Cant get Resource type: " + std::to_string(RAH_RESOURCE_TYPE_TOTAL);
			RAH_SAVELOG(logtxt);
			return returnResource;
		}
		if (_resourceType != RAH_DEFAULT)
		{
			for (size_t i = 0; i < m_resources[_resourceType]->size(); i++)
			{
				if (m_resources[_resourceType]->at(i)->m_id.Get() == _id)
				{
					returnResource = m_resources[_resourceType]->at(i);
					return returnResource;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < RAH_TOTAL; i++)
			{
				for (size_t j = 0; j < m_resources[i]->size(); j++)
				{
					if (m_resources[i]->at(j)->m_id.Get() == _id)
					{
						returnResource = m_resources[i]->at(j);
						return returnResource;
					}
				}
			}
		}
		GetLastError() = RAH_CANT_GET_RESOURCE;
		std::string logtxt;
		logtxt = "Cant get Resource type: " + std::to_string(RAH_CANT_GET_RESOURCE);
		RAH_SAVELOG(logtxt);
		return returnResource;
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

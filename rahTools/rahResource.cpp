#include "rahResource.h"


namespace rah
{
	RahResult rahResource::Initialize(BasicResourceParams* _params)
	{
		m_name.Set(_params->name);
		m_fileName.Set(_params->fileName);
		m_referenceCount.Set(1);
		m_id.Set(_params->id);
		return RahResult::RAH_SUCCESS;
	}
	void rahResource::Destroy()
	{
		m_referenceCount.Set(m_referenceCount.Get() - 1);
		m_name.Set(std::string(""));
		m_fileName.Set(std::string(""));
		m_id.Set(0);
	}
	rahResource::rahResource()
	{
	}

	rahResource::rahResource(BasicResourceParams* _params)
	{
		Initialize(_params);
	}

	rahResource::rahResource(BasicResourceParams _params)
	{
		Initialize(&_params);
	}


	rahResource::~rahResource()
	{
	}
}
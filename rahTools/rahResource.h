#pragma once
#include <string>
#include "rahMacros.h"
namespace rah
{
	/*
	* Basic struct to generate any resource
	*
	*/
	struct BasicResourceParams
	{
		std::string name;
		std::string fileName;
		int id;
	};
	/*
	* Basic container for any resource
	*
	*/
	class rahResource
	{
	public:
		SecuredVar<std::string> m_name;
		SecuredVar<std::string> m_fileName;
		SecuredVar<int> m_referenceCount;
		SecuredVar<int> m_id;
	public:
		/*
		* Initi basic for any resource this should call frist this them do it the son class 
		*
		*/
		virtual RahResult Initialize(BasicResourceParams* _params);
		/*
		* Remove the reference of this and empty the others constructors 
		*
		*/
		virtual void Destroy();
		/*
		* Load is the obigatory function this should be called after initialize or during this
		*
		*/
		virtual RahResult Load() = 0;
		rahResource();
		rahResource(BasicResourceParams* _params);
		rahResource(BasicResourceParams _params);
		virtual ~rahResource();
	};
}



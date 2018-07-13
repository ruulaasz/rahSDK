#pragma once
#include "rahMacros.h"
namespace rah
{
	template<class _type, class structInit>
	class Module
	{
	protected:
		static _type*& instance() {
			static _type* inst = NULL;
			return inst;
		}
		static RahResult& LastError() {
			static RahResult lastError = RAH_NOT_DECLARATE;
			return lastError;
		}
	public:
		static RahResult GetLastError()
		{
			return LastError();
		}
		static RahResult StartModule(structInit initValue)
		{
			if (instance() != NULL)
			{
				LastError() = RAH_ALREADY_DECLARATE;
				return LastError();
			}

			instance() = new _type();
			LastError() = instance()->Initialize(initValue);
			return LastError();
		}
		static _type& GetInstance()
		{
			if (instance() == NULL)
				LastError() = RAH_NOT_DECLARATE;
			return *instance();
		}
		static _type* GetPointerInstance()
		{
			if (instance() == NULL)
				LastError() = RAH_NOT_DECLARATE;
			return instance();
		}
		static void CloseModule()
		{
			LastError() = RAH_IS_DELETE;
			delete instance();
			instance() = NULL;
		}
	public:
		Module() {}
		virtual ~Module() {}
	};
}
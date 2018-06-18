#pragma once
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

	public:
		static RahResult StartModule(structInit initValue)
		{
			instance() = new _type();
			return instance()->Initialize(initValue);
		}
		static _type& GetInstance()
		{
			return *instance();
		}
		static _type* GetPointerInstance()
		{
			return instance();
		}
		static void CloseModule()
		{
			delete instance();
			instance() = NULL;
		}
	public:
		Module() {}
		virtual ~Module() {}
	};
}
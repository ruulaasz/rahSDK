#pragma once
#include "rahResource.h"
namespace rah
{
	class BasicResourceFabric
	{
	public:
		virtual rahResource* GetMemory(int _type) = 0;
		BasicResourceFabric();
		virtual ~BasicResourceFabric();
	};
}

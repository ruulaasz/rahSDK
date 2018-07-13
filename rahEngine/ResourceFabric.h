#pragma once
#include <rahTools.h>
namespace rah
{
	class ResourceFabric : public rah::BasicResourceFabric 
	{
	public:
		virtual rahResource* GetMemory(ResourceTypes _type);
		ResourceFabric();
		~ResourceFabric();
	};
}

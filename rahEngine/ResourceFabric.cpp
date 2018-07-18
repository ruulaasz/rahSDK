#include "ResourceFabric.h"
#include <rahGraphics.h>

namespace rah
{
	rahResource * ResourceFabric::GetMemory(ResourceTypes _type)
	{
		switch (_type)
		{
		case rah::RAH_DEFAULT:
			return NULL;
		case rah::RAH_GraphicTexture:
			return new rah::GraphicTexture;
		case rah::RAH_Material:
			return new rah::Material;
		case rah::RAH_Mesh:
			return new rah::Mesh;
		case rah::RAH_Model:
			return new rah::Model;
		case rah::RAH_TOTAL:
			return NULL;
		default:
			return NULL;
		}
	}
	ResourceFabric::ResourceFabric()
	{
	}


	ResourceFabric::~ResourceFabric()
	{
	}
}
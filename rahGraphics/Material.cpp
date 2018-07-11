#include "Material.h"

namespace rah
{
	Material::Material()
	{
		for (int i = 0; i < TextureType_MAXTEXTURES; i++)
		{
			m_textures[i] = nullptr;
		}
	}

	Material::~Material()
	{

	}

	RahResult Material::Load()
	{
		return RahResult();
	}
}
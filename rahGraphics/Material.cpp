#include "Material.h"

namespace rah
{
	Material::Material()
	{
		for (int i = 0; i < TextureType_MAXTEXTURES; i++)
		{
			m_graphicTextures[i] = NULL;
		}
	}

	Material::~Material()
	{

	}

	RahResult Material::Load()
	{
		return RahResult();
	}
	void Material::Release()
	{
		for (int i = 0; i < TextureType_MAXTEXTURES; i++)
		{
			if (m_graphicTextures[i])
			{
				m_graphicTextures[i]->Release();
				RAH_SAFE_DELETE(m_graphicTextures[i]);
				m_graphicTextures[i] = NULL;
			}
		}
	}
}
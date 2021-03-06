#pragma once

#include <d3d11.h>
#include <rahResource.h>
#include "GraphicTexture.h"

namespace rah
{
	/**
	* Enum of the texture types allowed
	*/
	enum TextureType
	{
		TextureType_NONE = 0,
		TextureType_DIFFUSE,
		TextureType_SPECULAR,
		TextureType_AMBIENT,
		TextureType_EMiSSIVE,
		TextureType_HEIGHT,
		TextureType_NORMALS,
		TextureType_SHININESS,
		TextureType_OPACITY,
		TextureType_DISPLACEMENT,
		TextureType_LIGHTMAP,
		TextureType_REFLECTION,
		TextureType_MAXTEXTURES
	};

	/**
	* A container for a material object
	*/
	class Material: public rahResource
	{
	public:
		Material();
		~Material();

		virtual RahResult Load();
		virtual void Release();

		GraphicTexture* m_graphicTextures[TextureType_MAXTEXTURES];
	};
}
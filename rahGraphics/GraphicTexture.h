#pragma once

#include <d3d11.h>
#include <string>
#include <rahResource.h>

namespace rah
{
	/**
	* Directx Texture
	*/
	class GraphicTexture : public rahResource
	{
	public:
		GraphicTexture();
		~GraphicTexture();

		/**
		* Fill an input layout using the vertex shader blob data
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _route
		* The file route
		*
		*/
		void loadFromFile(std::string _route);

		/*
		* Load is the obigatory function this should be called after initialize or during this
		*
		*/
		virtual RahResult Load();

		ID3D11ShaderResourceView* m_graphicTexture;
	};
}
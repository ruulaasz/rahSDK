#pragma once

#include <d3d11.h>
#include <string>

namespace rah
{
	/**
	* Directx Texture
	*/
	class GraphicTexture
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

		ID3D11ShaderResourceView* m_graphicTexture;
	};
}
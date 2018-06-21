#pragma once

#include <d3d11.h>
#include <string>

using std::string;

namespace rah
{
	class GraphicDevice;

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
		void loadFromFile(GraphicDevice* _device, string _route);

		void Load() {};
		void Unload() {};

		ID3D11ShaderResourceView* m_graphicTexture;
	};
}
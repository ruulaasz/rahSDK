#pragma once

#include <d3d11.h>

namespace rah
{
	/**
	* Create 2d textures as render targets or depth stencils
	*/
	class Texture2D
	{
	public:
		Texture2D();
		~Texture2D();

		/**
		* Creates a 2d texture as a render target texture
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _w
		* The width of the client screen
		*
		* @param _h
		* The height of the client screen
		*
		*/
		void CreateAsRenderTarget(UINT _w, UINT _h);

		/**
		* Creates a 2d texture as a depth stencil texture
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _w
		* The width of the client screen
		*
		* @param _h
		* The height of the client screen
		*
		*/
		void CreateAsDepthStencil(UINT _w, UINT _h, UINT _MipLevels = 1, UINT _ArraySize = 1, UINT SampleDesc = 1, UINT _CPUAccessFlags = 0, UINT _MiscFlags = 0);

		ID3D11Texture2D* m_texture;
	};
}
#pragma once

#include <d3d11.h>

namespace rah
{
	/**
	* Container for a render target object
	*/
	class RenderTarget
	{
	public:
		RenderTarget();
		~RenderTarget();

		ID3D11RenderTargetView* m_renderTarget;
	};
}
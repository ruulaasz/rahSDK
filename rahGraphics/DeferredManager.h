#pragma once

#include <rahTools.h>
#include "rahGraphics.h"

namespace rah
{
	class DeferredManager : public rah::Module<DeferredManager, void*>
	{
	public:
		DeferredManager();
		~DeferredManager();
		void Release();
		RahResult Initialize(void* _init);

		Texture2D m_renderTexture[8];
		RenderTarget m_renderTarget[8];
		ID3D11RenderTargetView* pRenderTargets[8];

		void setRenderTargets();
	};
}
#include "GraphicSwapChain.h"

namespace rah
{
	GraphicSwapChain::GraphicSwapChain()
	{
		m_swapChain = nullptr;
	}

	GraphicSwapChain::~GraphicSwapChain()
	{
		Release();
	}
}
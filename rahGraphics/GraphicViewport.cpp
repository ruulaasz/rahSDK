#include "GraphicViewport.h"
#include <d3d11.h>

namespace rah
{
	GraphicViewport::GraphicViewport()
	{
		m_viewport = nullptr;
	}

	GraphicViewport::~GraphicViewport()
	{
		Release();
	}

	void GraphicViewport::Set(void* _data)
	{
		m_viewport = static_cast<D3D11_VIEWPORT*>(_data);
	}
}
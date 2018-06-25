#include "Buffer.h"
#include "GraphicManager.h"

namespace rah
{
	Buffer::Buffer()
	{
		m_buffer = nullptr;
	}

	Buffer::~Buffer()
	{
		
	}

	void Buffer::create(D3D11_BUFFER_DESC * _desc, D3D11_SUBRESOURCE_DATA * _initData)
	{
		ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr());

		if (!pD3DDevice)
		{
			throw "NullPointer _device";
		}

		pD3DDevice->CreateBuffer(_desc, _initData, &m_buffer);
		if (!m_buffer)
		{
			throw "CreationFailed m_buffer";
		}
	}
}
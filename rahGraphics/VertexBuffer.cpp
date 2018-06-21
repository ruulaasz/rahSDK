#include "GraphicDevice.h"
#include "VertexBuffer.h"

namespace rah
{
	VertexBuffer::VertexBuffer()
	{

	}

	VertexBuffer::~VertexBuffer()
	{
		m_vertexInfo.clear();
	}

	void VertexBuffer::create(GraphicDevice* _device, unsigned int _creationFlags)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		unsigned int UsageFlag = D3D11_USAGE_DEFAULT;
		if (_creationFlags & VB_CREATE_STATIC)
		{
			UsageFlag = D3D11_USAGE_IMMUTABLE;
		}
		if (_creationFlags & VB_CREATE_DYNAMIC)
		{
			UsageFlag = D3D11_USAGE_DYNAMIC;
		}

		unsigned int CPUAccess = 0;
		if (_creationFlags & CPU_ACCESS_READ)
		{
			UsageFlag = D3D11_CPU_ACCESS_READ;
		}
		if (_creationFlags & CPU_ACCESS_WRITE)
		{
			UsageFlag = D3D11_CPU_ACCESS_WRITE;
		}

		bd.Usage = static_cast<D3D11_USAGE>(UsageFlag);
		bd.ByteWidth = m_vertexInfo.size() * sizeof(VertexData);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = CPUAccess;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = &m_vertexInfo[0];

		ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(_device->getPtr());
		if (!pD3DDevice)
		{
			throw "NullPointer _device";
		}

		pD3DDevice->CreateBuffer(&bd, &InitData, &m_buffer);
		if (!m_buffer)
		{
			throw "CreationFailed m_buffer";
		}
	}

	void VertexBuffer::addVertex(VertexData _vertex)
	{
		m_vertexInfo.push_back(_vertex);
	}
}
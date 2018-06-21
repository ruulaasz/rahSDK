#include "GraphicDevice.h"
#include "IndexBuffer.h"

namespace rah
{
	IndexBuffer::IndexBuffer()
	{

	}

	IndexBuffer::~IndexBuffer()
	{
		m_indexArray.clear();
	}

	void IndexBuffer::create(GraphicDevice* _device, unsigned int _creationFlags)
	{
		if (!_device)
		{
			throw "NullPointer _device";
		}

		if (!m_indexArray.empty())
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));

			unsigned int UsageFlag = D3D11_USAGE_DEFAULT;
			if (_creationFlags & IB_CREATE_STATIC)
			{
				UsageFlag = D3D11_USAGE_IMMUTABLE;
			}
			if (_creationFlags & IB_CREATE_DYNAMIC)
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
			bd.ByteWidth = m_indexArray.size() * sizeof(unsigned int);
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = CPUAccess;

			D3D11_SUBRESOURCE_DATA InitData;
			ZeroMemory(&InitData, sizeof(InitData));
			InitData.pSysMem = &m_indexArray[0];

			ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(_device->getPtr());
			pD3DDevice->CreateBuffer(&bd, &InitData, &m_buffer);
			if (!m_buffer)
			{
				throw "CreationFailed m_buffer";
			}
		}
		else
		{
			throw "Empty m_indexArray";
		}
	}

	void IndexBuffer::addIndex(unsigned int _index)
	{
		m_indexArray.push_back(_index);
	}
}

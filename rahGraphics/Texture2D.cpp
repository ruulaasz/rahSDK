#include "GraphicDevice.h"
#include "Texture2D.h"

namespace rah
{
	Texture2D::Texture2D()
	{
		m_texture = nullptr;
	}

	Texture2D::~Texture2D()
	{

	}

	void Texture2D::CreateAsRenderTarget(const GraphicDevice * _device, UINT _w, UINT _h)
	{
		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(_device->getPtr());
		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));

		desc.Width = _w;
		desc.Height = _h;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		pDevice->CreateTexture2D(&desc, nullptr, &m_texture);
		if (!m_texture)
		{
			throw "NullPointer m_texture";
		}
	}

	void Texture2D::CreateAsDepthStencil(const GraphicDevice* _device, UINT _w, UINT _h, UINT _MipLevels, UINT _ArraySize, UINT SampleDesc, UINT _CPUAccessFlags, UINT _MiscFlags)
	{
		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(_device->getPtr());
		if (!m_texture)
		{
			throw "NullPointer m_texture";
		}

		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
		descDepth.Width = _w;
		descDepth.Height = _h;
		descDepth.MipLevels = _MipLevels;
		descDepth.ArraySize = _ArraySize;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = SampleDesc;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = _CPUAccessFlags;
		descDepth.MiscFlags = _MiscFlags;

		pDevice->CreateTexture2D(&descDepth, nullptr, &m_texture);
		if (!m_texture)
		{
			throw "NullPointer m_texture";
		}
	}
}
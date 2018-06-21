#include "GraphicTexture.h"
#include <DirectXTex.h>
#include "GraphicDevice.h"

using std::wstring;

namespace rah
{
	GraphicTexture::GraphicTexture()
	{
		m_graphicTexture = nullptr;
	}

	GraphicTexture::~GraphicTexture()
	{

	}

	void GraphicTexture::loadFromFile(GraphicDevice* _device, string _route)
	{
		if (_route.empty())
		{
			throw "Empty _route";
		}

		if (!_device)
		{
			throw "CreationFailed m_buffer";
		}
		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(_device->getPtr());

		DirectX::ScratchImage Image;
		wstring wide_string = wstring(_route.begin(), _route.end());
		const wchar_t* result = wide_string.c_str();
		DirectX::LoadFromDDSFile(result, 0, nullptr, Image);
		if (Image.GetImageCount() < 1)
		{
			throw "CreationFailed Image";
		}

		DirectX::CreateShaderResourceView(pDevice, Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &m_graphicTexture);
		if (!m_graphicTexture)
		{
			throw "CreationFailed m_texture";
		}
	}
}
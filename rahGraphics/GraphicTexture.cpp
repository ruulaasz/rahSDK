#include "GraphicDevice.h"
#include "GraphicTexture.h"
#include <DirectXTex.h>

using std::wstring;

namespace rah
{
	Texture::Texture()
	{
		m_texture = nullptr;
	}

	Texture::~Texture()
	{

	}

	void Texture::loadFromFile(GraphicDevice* _device, string _route)
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

		DirectX::CreateShaderResourceView(pDevice, Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &m_texture);
		if (!m_texture)
		{
			throw "CreationFailed m_texture";
		}
	}
}
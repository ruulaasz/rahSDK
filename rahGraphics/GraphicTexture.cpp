#include "GraphicTexture.h"
#include <DirectXTex.h>
#include "GraphicManager.h"

namespace rah
{
	GraphicTexture::GraphicTexture()
	{
		m_graphicTexture = nullptr;
	}

	GraphicTexture::~GraphicTexture()
	{

	}

	void GraphicTexture::loadFromFile(std::string _route)
	{
		ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr());

		if (_route.empty())
		{
			throw "Empty _route";
		}

		if (!pD3DDevice)
		{
			throw "CreationFailed m_buffer";
		}
		
		DirectX::ScratchImage Image;
		std::wstring wide_string = std::wstring(_route.begin(), _route.end());
		const wchar_t* result = wide_string.c_str();
		DirectX::LoadFromDDSFile(result, 0, nullptr, Image);
		if (Image.GetImageCount() < 1)
		{
			throw "CreationFailed Image";
		}

		DirectX::CreateShaderResourceView(pD3DDevice, Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &m_graphicTexture);
		if (!m_graphicTexture)
		{
			throw "CreationFailed m_texture";
		}
	}

	RahResult GraphicTexture::Load()
	{
		ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr());

		std::string fileName = m_filePath.Get();

		if (fileName.empty())
		{
			throw "Empty _route";
		}

		if (!pD3DDevice)
		{
			throw "CreationFailed m_buffer";
		}

		DirectX::ScratchImage Image;
		std::wstring wide_string = std::wstring(fileName.begin(), fileName.end());
		const wchar_t* result = wide_string.c_str();
		DirectX::LoadFromDDSFile(result, 0, nullptr, Image);
		if (Image.GetImageCount() < 1)
		{
			throw "CreationFailed Image";
		}

		DirectX::CreateShaderResourceView(pD3DDevice, Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &m_graphicTexture);
		if (!m_graphicTexture)
		{
			throw "CreationFailed m_texture";
		}

		return RahResult();
	}
	void GraphicTexture::Release()
	{
	}
}
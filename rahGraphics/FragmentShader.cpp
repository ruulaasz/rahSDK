#include "FragmentShader.h"
#include "GraphicManager.h"

namespace rah
{
	FragmentShader::FragmentShader()
	{
		m_fragmentShader = nullptr;
	}

	FragmentShader::~FragmentShader()
	{

	}

	void rah::FragmentShader::createFragmentShader(WCHAR * _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel)
	{
		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr());

		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		compileShaderFromFile(_szFileName, _szEntryPoint, _szShaderModel, &m_shaderBlob);
		if (!m_shaderBlob)
		{
			throw "CreationFailed m_shaderBlob";
		}

		pDevice->CreatePixelShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), NULL, &m_fragmentShader);
		if (!m_fragmentShader)
		{
			m_shaderBlob->Release();
			throw "CreationFailed m_fragmentShader";
		}
	}
}
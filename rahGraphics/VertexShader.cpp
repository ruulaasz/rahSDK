#include "VertexShader.h"
#include "GraphicManager.h"

namespace rah
{
	VertexShader::VertexShader()
	{
		m_vertexShader = nullptr;
	}

	VertexShader::~VertexShader()
	{

	}

	void VertexShader::createVertexShader(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel)
	{
		ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr());

		compileShaderFromFile(_szFileName, _szEntryPoint, _szShaderModel, &m_shaderBlob);
		if (!m_shaderBlob)
		{
			throw "CreationFailed m_shaderBlob";
		}

		pD3DDevice->CreateVertexShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), nullptr, &m_vertexShader);
		if (!m_vertexShader)
		{
			m_shaderBlob->Release();
			throw "CreationFailed m_vertexShader";
		}
	}
}
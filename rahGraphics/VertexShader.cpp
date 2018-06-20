#include "VertexShader.h"

namespace rah
{
	VertexShader::VertexShader()
	{
		m_vertexShader = nullptr;
	}

	VertexShader::~VertexShader()
	{

	}

	void VertexShader::createVertexShader(ID3D11Device* _device, WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel)
	{
		compileShaderFromFile(_szFileName, _szEntryPoint, _szShaderModel, &m_shaderBlob);
		if (!m_shaderBlob)
		{
			throw "CreationFailed m_shaderBlob";
		}

		_device->CreateVertexShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), nullptr, &m_vertexShader);
		if (!m_vertexShader)
		{
			m_shaderBlob->Release();
			throw "CreationFailed m_vertexShader";
		}
	}
}
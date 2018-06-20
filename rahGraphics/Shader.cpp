#include "Shader.h"

namespace rah
{
	Shader::Shader()
	{
		m_shaderBlob = nullptr;
	}

	Shader::~Shader()
	{

	}

	void Shader::compileShaderFromFile(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3DBlob** _ppBlobOut)
	{
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob = nullptr;
		D3DCompileFromFile(_szFileName, nullptr, nullptr, _szEntryPoint, _szShaderModel, dwShaderFlags, 0, _ppBlobOut, &pErrorBlob);

		if (!_ppBlobOut)
		{
			if (pErrorBlob)
			{
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
				pErrorBlob->Release();
				throw "CreationFailed D3DCompileFromFile";
			}

			throw "CreationFailed D3DCompileFromFile";
		}
	}
}
#include "InputLayout.h"
#include "GraphicManager.h"
#include <d3dcompiler.h>

namespace rah
{
	InputLayout::InputLayout()
	{
		m_layoutArray = nullptr;
		m_inputLayout = nullptr;
		m_layoutElements = 0;
	}

	InputLayout::~InputLayout()
	{
		delete[] m_layoutArray;

		if (m_inputLayout)
		{
			m_inputLayout->Release();
		}
	}

	void InputLayout::createInputLayoutFromVertexShaderSignature(ID3DBlob* _pShaderBlob)
	{
		ID3D11ShaderReflection* pVertexShaderReflection = nullptr;

		D3DReflect(_pShaderBlob->GetBufferPointer(), _pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection);

		if (!pVertexShaderReflection)
		{
			throw "CreationFailed pVertexShaderReflection";
		}

		D3D11_SHADER_DESC shaderDesc;
		pVertexShaderReflection->GetDesc(&shaderDesc);

		m_layoutArray = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
		m_layoutElements = shaderDesc.InputParameters;

		for (int i = 0; i < (int)shaderDesc.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

			// fill out input element desc
			D3D11_INPUT_ELEMENT_DESC elementDesc;
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 0;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;

			// determine DXGI format
			if (paramDesc.Mask == 1)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (paramDesc.Mask <= 3)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (paramDesc.Mask <= 7)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (paramDesc.Mask <= 15)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			m_layoutArray[i] = elementDesc;
		}

		if (!m_layoutArray)
		{
			throw "CreationFailed m_layoutArray";
		}

		createInputLayout(_pShaderBlob);
	}

	void InputLayout::createInputLayout(ID3DBlob* _pVSBlob)
	{
		ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr());

		pD3DDevice->CreateInputLayout(m_layoutArray, m_layoutElements, _pVSBlob->GetBufferPointer(), _pVSBlob->GetBufferSize(), &m_inputLayout);
		_pVSBlob->Release();

		if (!m_inputLayout)
		{
			throw "CreationFailed m_inputLayout";
		}
	}
}
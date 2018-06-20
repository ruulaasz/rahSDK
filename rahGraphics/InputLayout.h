#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

namespace rah
{
	/**
	* Create and manage an input layout
	*/
	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		/**
		* Fill an input layout using the vertex shader blob data
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _pVSBlob
		* The blob with the vertex shader data
		*
		*/
		void createInputLayoutFromVertexShaderSignature(ID3D11Device* _device, ID3DBlob* _pVSBlob);

		/**
		* Creates an input layout using the previously filled data
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _pVSBlob
		* The blob with the vertex shader data
		*
		*/
		void createInputLayout(ID3D11Device* _device, ID3DBlob* _pVSBlob);

		ID3D11InputLayout* m_inputLayout;

	private:
		D3D11_INPUT_ELEMENT_DESC* m_layoutArray;
		unsigned int m_layoutElements;
	};
}
#pragma once

#include "InputLayout.h"

namespace rah
{
	/**
	* Base class for a graphic shader.
	*/
	class Shader
	{
	public:
		Shader();
		~Shader();

		/**
		* Fill an input layout using the vertex shader blob data
		*
		* @param _szFileName
		* The name of the shader file
		*
		* @param _szEntryPoint
		* The entry point of the shader
		*
		* @param _szShaderModel
		* The shader model
		*
		* @out _ppBlobOut
		* A shader data blob
		*
		*/
		void compileShaderFromFile(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3DBlob** _ppBlobOut);

		ID3DBlob* m_shaderBlob;
		InputLayout m_inputLayout;
	};
}
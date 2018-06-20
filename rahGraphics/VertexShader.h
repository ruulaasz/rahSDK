#pragma once
#include "Shader.h"

namespace rah
{
	/**
	* Create and manage a vertex shader
	*/
	class VertexShader : public Shader
	{
	public:
		VertexShader();
		~VertexShader();

		/**
		*  Load and create a vertex shader interface
		*
		* @param _device
		* Reference to a graphic device
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
		*/
		void createVertexShader(ID3D11Device* _device, WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel);

		ID3D11VertexShader* m_vertexShader;
	};
}
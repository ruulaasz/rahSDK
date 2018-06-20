#pragma once

#include "Shader.h"

namespace rah
{
	class GraphicDevice;

	/**
	* Create and manage a fragment shader
	*/
	class FragmentShader : public Shader
	{
	public:
		FragmentShader();
		~FragmentShader();

		/**
		* Load and create a fragment shader interface
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
		void createFragmentShader(const GraphicDevice* _device, WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel);

		ID3D11PixelShader* m_fragmentShader;
	};
}
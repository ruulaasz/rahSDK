#pragma once

#include "FragmentShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"
#include "GraphicDevice.h"
#include "Texture2D.h"
#include "GraphicSwapChain.h"
#include "GraphicDeviceContext.h"
#include "GraphicDepthStencilView.h"
#include "GraphicSamplerState.h"
#include "GraphicViewport.h"
#include <rahTools.h>

namespace rah
{
	struct InitStruct
	{
		UINT w;
		UINT h;
	};

	/**
	* Manager class for all the graphic objects and inicialitation
	*/
	class GraphicManager : public rah::Module<GraphicManager, InitStruct>
	{
	public:
		GraphicManager();
		~GraphicManager();

		RahResult Initialize(InitStruct ptr);

		/**
		* Creates a graphic device and swap chain
		*
		* @param _hwnd
		* Reference to a window handler
		*
		* @param _bufferCount = 1
		* The buffer count for the swap chain
		*
		* @param _sampleCount = 1
		* The sampler count for the swap chain
		*
		*/
		void createDeviceAndSwapchain(HWND _hwnd, UINT _bufferCount = 1, UINT _sampleCount = 1);

		/**
		* Creates the back buffer
		*
		*/
		void createBackBuffer();

		/**
		* Creates a render target view
		*
		* @param _renderTargetView
		* Reference to a render target view
		*
		* @param _renderTexture
		* The texture binded to the render target view
		*
		*/
		void createRenderTargetView(RenderTarget* _renderTargetView, const Texture2D* _renderTexture);

		/**
		* Creates a depthstencil texture and depth stencil view
		*
		* @param _MipLevels = 1
		* The mip levels
		*
		* @param _ArraySize = 1
		* The array size
		*
		* @param SampleDesc = 1
		* The sampler count
		*
		* @param _CPUAccessFlags = 0
		* The CPU access flags
		*
		* @param _MiscFlags = 0
		* The miscelaneous flags
		*
		*/
		void createDepthStencilView(UINT _mipLevels = 1, UINT _arraySize = 1, UINT _sampleCount = 1, UINT _CPUAccessFlags = 0, UINT _miscFlags = 0);

		/**
		* Creates the depth stencil state
		*
		*/
		void createDepthStencilState();

		/**
		* Creates the razterizer states
		*
		*/
		void createRazterizerStates();

		/**
		* Creates a viewport
		*
		* @param _MinDepth = 0.0f
		* The mip depth
		*
		* @param _MaxDepth = 1.0f
		* The max depth
		*
		* @param _TopLeftX = 0.0f
		* The initial x position
		*
		* @param _TopLeftY = 0.0f
		* The initial y position
		*
		*/
		void createViewport(FLOAT _minDepth = 0.0f, FLOAT _maxDepth = 1.0f, FLOAT _topLeftX = 0.0f, FLOAT _topLeftY = 0.0f);

		/**
		* Cleans the given render target using the giving color
		*
		* @param _renderTarget
		* Reference to a render target view
		*
		* @param _color
		* The color of the cleaned screen
		*
		*/
		void clearScreen(RenderTarget* _renderTarget, float _color[4] = {});

		/**
		* Releases all objects memory
		*
		*/
		void cleanDevice();

		/**
		* Cleans the given render target using the giving color
		*
		* @param _hwnd
		* Reference to a window handler
		*
		*/
		void init(HWND _hwnd);

		GraphicSwapChain m_swapchain;
		GraphicDevice m_device;
		GraphicDeviceContext m_deviceContext;
		RenderTarget m_renderTarget;
		UINT m_driverType;
		D3D_FEATURE_LEVEL m_featureLevel;
		Texture2D m_depthStencil;
		Texture2D m_backBuffer;
		GraphicDepthStencilView m_depthStencilView;
		GraphicSamplerState m_samplerState;
		GraphicViewport m_viewport;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11RasterizerState* m_rasterizerState[3];

		UINT m_width;
		UINT m_height;
	};
}
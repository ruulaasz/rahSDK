#include "GraphicManager.h"

namespace rah
{
	GraphicManager::GraphicManager()
	{
		m_driverType = D3D_DRIVER_TYPE_NULL;
		m_featureLevel = D3D_FEATURE_LEVEL_11_0;
		m_width = 100;
		m_height = 100;
		m_depthStencilState = nullptr;
	}

	GraphicManager::~GraphicManager()
	{

	}

	RahResult GraphicManager::Initialize(InitStruct ptr)
	{
		m_width = ptr.w;
		m_height = ptr.h;

		return RAH_SUCCESS;
	}

	void GraphicManager::createDeviceAndSwapchain(HWND _hwnd, UINT _bufferCount, UINT _sampleDesc)
	{
		RECT rc;
		GetClientRect(_hwnd, &rc);
		m_width = rc.right - rc.left;
		m_height = rc.bottom - rc.top;

		UINT createDeviceFlags = 0;

#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};

		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = _bufferCount;
		sd.BufferDesc.Width = m_width;
		sd.BufferDesc.Height = m_height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = _hwnd;
		sd.SampleDesc.Count = _sampleDesc;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		ID3D11Device** pDevice = reinterpret_cast<ID3D11Device**>(m_device.getReference());
		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		IDXGISwapChain** pSwapChain = reinterpret_cast<IDXGISwapChain**>(m_swapchain.getReference());
		if (!pSwapChain)
		{
			throw "NullPointer pSwapChain";
		}

		ID3D11DeviceContext** pDeviceContext = reinterpret_cast<ID3D11DeviceContext**>(m_deviceContext.getReference());
		if (!pDeviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		HRESULT hr = S_OK;
		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			m_driverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain(nullptr, static_cast<D3D_DRIVER_TYPE>(m_driverType), nullptr,
				createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &sd, pSwapChain, pDevice, &m_featureLevel, pDeviceContext);
			if (SUCCEEDED(hr))
				break;
		}

		if (FAILED(hr))
		{
			throw "CreationFailed D3D11CreateDeviceAndSwapChain";
		}
	}

	void GraphicManager::createBackBuffer()
	{
		IDXGISwapChain* pSwapChain = reinterpret_cast<IDXGISwapChain*>(m_swapchain.getPtr());
		if (!pSwapChain)
		{
			throw "NullPointer pSwapChain";
		}

		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(m_device.getPtr());
		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer);
		if (!m_backBuffer.m_texture)
		{
			throw "NullPointer m_backBuffer";
		}

		pDevice->CreateRenderTargetView(m_backBuffer.m_texture, nullptr, &m_renderTarget.m_renderTarget);
		if (!m_renderTarget.m_renderTarget)
		{
			throw "NullPointer m_renderTarget";
		}
	}

	void GraphicManager::createRenderTargetView(RenderTarget* _renderTargetView, const Texture2D* _renderTexture)
	{
		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(m_device.getPtr());
		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		pDevice->CreateRenderTargetView(_renderTexture->m_texture, nullptr, &_renderTargetView->m_renderTarget);
		if (!m_renderTarget.m_renderTarget)
		{
			throw "NullPointer m_renderTarget";
		}
	}

	void GraphicManager::createDepthStencilView(UINT _mipLevels, UINT _arraySize, UINT _sampleDesc, UINT _CPUAccessFlags, UINT _miscFlags)
	{
		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
		descDepth.Width = m_width;
		descDepth.Height = m_height;
		descDepth.MipLevels = _mipLevels;
		descDepth.ArraySize = _arraySize;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = _sampleDesc;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = _CPUAccessFlags;
		descDepth.MiscFlags = _miscFlags;

		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(m_device.getPtr());
		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		pDevice->CreateTexture2D(&descDepth, nullptr, &m_depthStencil.m_texture);
		if (!m_depthStencil.m_texture)
		{
			throw "NullPointer m_depthStencil";
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		ID3D11DepthStencilView** pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView**>(m_depthStencilView.getReference());
		if (!pDepthStencilView)
		{
			throw "NullPointer pDepthStencilView";
		}

		pDevice->CreateDepthStencilView(m_depthStencil.m_texture, &descDSV, pDepthStencilView);
		if (!pDepthStencilView)
		{
			throw "NullPointer pDepthStencilView";
		}
	}

	void GraphicManager::createDepthStencilState()
	{
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
		ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

		depthStencilStateDesc.DepthEnable = true;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilStateDesc.StencilEnable = false;
		depthStencilStateDesc.StencilReadMask = 0xFF;
		depthStencilStateDesc.StencilWriteMask = 0xFF;

		depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
		depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
		depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_ZERO;
		depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_ZERO;
		depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(m_device.getPtr());
		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		pDevice->CreateDepthStencilState(&depthStencilStateDesc, &m_depthStencilState);
		if (!m_depthStencilState)
		{
			throw "NullPointer m_depthStencilState";
		}
	}

	void GraphicManager::createRazterizerStates()
	{
		D3D11_RASTERIZER_DESC RasterizerDesc;
		ZeroMemory(&RasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

		RasterizerDesc.AntialiasedLineEnable = false;
		RasterizerDesc.CullMode = D3D11_CULL_BACK;
		RasterizerDesc.DepthBias = 0;
		RasterizerDesc.DepthBiasClamp = 0.06f;
		RasterizerDesc.DepthClipEnable = TRUE;
		RasterizerDesc.FrontCounterClockwise = false;
		RasterizerDesc.MultisampleEnable = false;
		RasterizerDesc.ScissorEnable = false;
		RasterizerDesc.SlopeScaledDepthBias = 0.06f;

		ID3D11Device* pDevice = reinterpret_cast<ID3D11Device*>(m_device.getPtr());
		if (!pDevice)
		{
			throw "NullPointer _device";
		}

		RasterizerDesc.FillMode = D3D11_FILL_SOLID;
		pDevice->CreateRasterizerState(&RasterizerDesc, &m_rasterizerState[0]);
		if (!m_rasterizerState[0])
		{
			throw "NullPointer m_rasterizerState0";
		}

		RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		pDevice->CreateRasterizerState(&RasterizerDesc, &m_rasterizerState[1]);
		if (!m_rasterizerState[1])
		{
			throw "NullPointer m_rasterizerState1";
		}

		RasterizerDesc.FillMode = D3D11_FILL_SOLID;
		RasterizerDesc.AntialiasedLineEnable = true;
		pDevice->CreateRasterizerState(&RasterizerDesc, &m_rasterizerState[2]);
		if (!m_rasterizerState[2])
		{
			throw "NullPointer m_rasterizerState2";
		}
	}

	void GraphicManager::createViewport(FLOAT _MinDepth, FLOAT _MaxDepth, FLOAT _TopLeftX, FLOAT _TopLeftY)
	{
		D3D11_VIEWPORT* pViewport = reinterpret_cast<D3D11_VIEWPORT*>(m_viewport.getPtr());

		pViewport = new D3D11_VIEWPORT;

		pViewport->MinDepth = _MinDepth;
		pViewport->MaxDepth = _MaxDepth;
		pViewport->TopLeftX = _TopLeftX;
		pViewport->TopLeftY = _TopLeftY;
		pViewport->Width = (float)m_width;
		pViewport->Height = (float)m_height;

		m_viewport.Set(pViewport);
	}

	void GraphicManager::clearScreen(RenderTarget* _renderTarget, Color _color)
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(m_deviceContext.getPtr());
		if (!pDeviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		if (!_renderTarget)
		{
			throw "NullPointer _renderTarget";
		}

		float color[4] = { _color.r, _color.g, _color.b, _color.alpha };

		pDeviceContext->ClearRenderTargetView(_renderTarget->m_renderTarget, color);
	}

	void GraphicManager::cleanDevice()
	{
		m_deviceContext.Release();
		if (m_depthStencil.m_texture) m_depthStencil.m_texture->Release();
		m_depthStencilView.Release();
		if (m_renderTarget.m_renderTarget) m_renderTarget.m_renderTarget->Release();
		m_swapchain.Release();
		m_device.Release();
	}

	void GraphicManager::init(HWND _hwnd)
	{
		if (!_hwnd)
		{
			throw "NullPointer _hwnd";
		}

		createDeviceAndSwapchain(_hwnd);
		createBackBuffer();
		createDepthStencilView();
		createDepthStencilState();
		createRazterizerStates();
		createViewport();
	}
	void GraphicManager::Release()
	{
		cleanDevice();
	}
}
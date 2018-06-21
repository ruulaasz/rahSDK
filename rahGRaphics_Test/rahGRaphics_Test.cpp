// rahGRaphics_Test.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "rahGRaphics_Test.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
#define MAX_LOADSTRING 100

// Variables globales:
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;

ID3D11Device* g_pD3DDevice;
IDXGISwapChain* g_pSwapChain;
ID3D11DeviceContext* g_pDeviceContext;
ID3D11DepthStencilView* g_pDepthStencilView;
ID3D11SamplerState* g_pSamplerState;
D3D11_VIEWPORT* g_pViewport;

float g_deltaTime = 0.0f;
float g_lastTime = 0.0f;
float g_currentTime = 0.0f;
int g_RasterizerState = 2;

struct SimpleVertex
{
	rah::Vector3D Pos;
	rah::Vector2D Tex;
};

struct CBView
{
	rah::Matrix4D mView;
};

struct CBProj
{
	rah::Matrix4D mProjection;
};

struct CBWorld
{
	rah::Matrix4D mWorld;
};

struct CBColor
{
	rah::Vector4D mColor;
};

rah::ConstantBuffer g_pVertexBuffer;
rah::ConstantBuffer g_pIndexBuffer;
rah::ConstantBuffer g_pCBView;
rah::ConstantBuffer g_pCBProj;
rah::ConstantBuffer g_pCBWorld;
rah::ConstantBuffer g_pCBColor;

rah::Matrix4D  g_World;
rah::Matrix4D  g_View;
rah::Matrix4D  g_Projection;
float colorbk[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

rah::RenderTarget g_renderTarget;
rah::Texture2D pBackBuffer;
rah::VertexShader g_vertexShader;
rah::FragmentShader g_pixelShader;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// this function initializes and prepares Direct3D for use
RahResult InitD3D(HWND hWnd)
{
	rah::InitStruct init;
	init.w = SCREEN_WIDTH;
	init.h = SCREEN_HEIGHT;
	rah::GraphicManager::StartModule(init);

	rah::GraphicManager::GetInstance().init(hWnd);

	g_pD3DDevice = reinterpret_cast<ID3D11Device*>(rah::GraphicManager::GetInstance().m_device.getPtr());
	g_pSwapChain = reinterpret_cast<IDXGISwapChain*>(rah::GraphicManager::GetInstance().m_swapchain.getPtr());
	g_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(rah::GraphicManager::GetInstance().m_deviceContext.getPtr());
	g_pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(rah::GraphicManager::GetInstance().m_depthStencilView.getPtr());
	g_pSamplerState = reinterpret_cast<ID3D11SamplerState*>(rah::GraphicManager::GetInstance().m_samplerState.getPtr());
	g_pViewport = reinterpret_cast<D3D11_VIEWPORT*>(rah::GraphicManager::GetInstance().m_viewport.getPtr());

	g_lastTime = GetTickCount();

	return RAH_SUCCESS;
}

void LoadContent()
{
	g_renderTarget = rah::GraphicManager::GetInstance().m_renderTarget;

	//g_vertexShader.createVertexShader(g_pD3DDevice, L"Tutorial07.fx", "VS", "vs_4_0");
	//g_vertexShader.m_inputLayout.createInputLayoutFromVertexShaderSignature(g_pD3DDevice, g_vertexShader.m_shaderBlob);

	//g_pDeviceContext->IASetInputLayout(g_vertexShader.m_inputLayout.m_inputLayout);

	//g_pixelShader.createFragmentShader(&rah::GraphicManager::GetInstance().m_device, L"Tutorial07.fx", "PS", "ps_4_0");


	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		{ rah::Vector3D(-1.0f, 1.0f, -1.0f), rah::Vector2D(0.0f, 0.0f) },
		{ rah::Vector3D(1.0f, 1.0f, -1.0f), rah::Vector2D(1.0f, 0.0f) },
		{ rah::Vector3D(1.0f, 1.0f, 1.0f), rah::Vector2D(1.0f, 1.0f) },
		{ rah::Vector3D(-1.0f, 1.0f, 1.0f), rah::Vector2D(0.0f, 1.0f) },

		{ rah::Vector3D(-1.0f, -1.0f, -1.0f), rah::Vector2D(0.0f, 0.0f) },
		{ rah::Vector3D(1.0f, -1.0f, -1.0f), rah::Vector2D(1.0f, 0.0f) },
		{ rah::Vector3D(1.0f, -1.0f, 1.0f), rah::Vector2D(1.0f, 1.0f) },
		{ rah::Vector3D(-1.0f, -1.0f, 1.0f), rah::Vector2D(0.0f, 1.0f) },

		{ rah::Vector3D(-1.0f, -1.0f, 1.0f), rah::Vector2D(0.0f, 0.0f) },
		{ rah::Vector3D(-1.0f, -1.0f, -1.0f), rah::Vector2D(1.0f, 0.0f) },
		{ rah::Vector3D(-1.0f, 1.0f, -1.0f), rah::Vector2D(1.0f, 1.0f) },
		{ rah::Vector3D(-1.0f, 1.0f, 1.0f), rah::Vector2D(0.0f, 1.0f) },

		{ rah::Vector3D(1.0f, -1.0f, 1.0f), rah::Vector2D(0.0f, 0.0f) },
		{ rah::Vector3D(1.0f, -1.0f, -1.0f), rah::Vector2D(1.0f, 0.0f) },
		{ rah::Vector3D(1.0f, 1.0f, -1.0f), rah::Vector2D(1.0f, 1.0f) },
		{ rah::Vector3D(1.0f, 1.0f, 1.0f), rah::Vector2D(0.0f, 1.0f) },

		{ rah::Vector3D(-1.0f, -1.0f, -1.0f), rah::Vector2D(0.0f, 0.0f) },
		{ rah::Vector3D(1.0f, -1.0f, -1.0f), rah::Vector2D(1.0f, 0.0f) },
		{ rah::Vector3D(1.0f, 1.0f, -1.0f), rah::Vector2D(1.0f, 1.0f) },
		{ rah::Vector3D(-1.0f, 1.0f, -1.0f), rah::Vector2D(0.0f, 1.0f) },

		{ rah::Vector3D(-1.0f, -1.0f, 1.0f), rah::Vector2D(0.0f, 0.0f) },
		{ rah::Vector3D(1.0f, -1.0f, 1.0f), rah::Vector2D(1.0f, 0.0f) },
		{ rah::Vector3D(1.0f, 1.0f, 1.0f), rah::Vector2D(1.0f, 1.0f) },
		{ rah::Vector3D(-1.0f, 1.0f, 1.0f), rah::Vector2D(0.0f, 1.0f) },
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;

	rah::GraphicManager g = rah::GraphicManager::GetInstance();

	g_pVertexBuffer.create(&g.m_device, &bd, &InitData);

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pDeviceContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer.m_buffer, &stride, &offset);

	//// Create index buffer
	//// Create vertex buffer
	//WORD indices[] =
	//{
	//	3,1,0,
	//	2,1,3,

	//	6,4,5,
	//	7,4,6,

	//	11,9,8,
	//	10,9,11,

	//	14,12,13,
	//	15,12,14,

	//	19,17,16,
	//	18,17,19,

	//	22,20,21,
	//	23,20,22
	//};

	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(WORD) * 36;
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//InitData.pSysMem = indices;
	//hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
	//if (FAILED(hr))
	//	return hr;

	//// Set index buffer
	//g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//// Set primitive topology
	//g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//// Create the constant buffers
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(CBNeverChanges);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBNeverChanges);
	//if (FAILED(hr))
	//	return hr;

	//bd.ByteWidth = sizeof(CBChangeOnResize);
	//hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBChangeOnResize);
	//if (FAILED(hr))
	//	return hr;

	//bd.ByteWidth = sizeof(CBChangesEveryFrame);
	//hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBChangesEveryFrame);
	//if (FAILED(hr))
	//	return hr;

	//// Load the Texture
	//hr = D3DX11CreateShaderResourceViewFromFile(g_pd3dDevice, L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL);
	//if (FAILED(hr))
	//	return hr;

	//// Create the sample state
	//D3D11_SAMPLER_DESC sampDesc;
	//ZeroMemory(&sampDesc, sizeof(sampDesc));
	//sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	//sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	//sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//sampDesc.MinLOD = 0;
	//sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//hr = g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
	//if (FAILED(hr))
	//	return hr;

	//// Initialize the world matrices
	//g_World = XMMatrixIdentity();

	//// Initialize the view matrix
	//XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	//XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//g_View = XMMatrixLookAtLH(Eye, At, Up);

	//CBNeverChanges cbNeverChanges;
	//cbNeverChanges.mView = XMMatrixTranspose(g_View);
	//g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);

	//// Initialize the projection matrix
	//g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

	//CBChangeOnResize cbChangesOnResize;
	//cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	//g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0);

	//return S_OK;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RAHGRAPHICS_TEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RAHGRAPHICS_TEST));

    MSG msg;

	InitD3D(g_hWnd);
	LoadContent();

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	rah::GraphicManager::CloseModule();
    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: registrar la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RAHGRAPHICS_TEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_RAHGRAPHICS_TEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: guardar el identificador de instancia y crear la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; // Almacenar identificador de instancia en una variable global

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO:  procesar mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

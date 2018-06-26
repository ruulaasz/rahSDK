// rahGRaphics_Test.cpp: define el punto de entrada de la aplicación.
#include "stdafx.h"
#include "rahGRaphics_Test.h"
#include <math.h>

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
	rah::Vector4D mColor;
};

rah::ConstantBuffer g_pVertexBuffer;
rah::ConstantBuffer g_pIndexBuffer;
rah::ConstantBuffer g_pCBView;
rah::ConstantBuffer g_pCBProj;
rah::ConstantBuffer g_pCBWorld;

rah::Matrix4D  g_World;
rah::Matrix4D  g_View;
rah::Matrix4D  g_Projection;
rah::Vector4D g_Color(1.f, 0.f, 0.f, 1.f);

rah::RenderTarget g_renderTarget;
rah::GraphicTexture g_texture;
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

	return RAH_SUCCESS;
}

void LoadContent()
{
	g_renderTarget = rah::GraphicManager::GetInstance().m_renderTarget;

	g_vertexShader.createVertexShader(L"Tutorial07.fx", "VS", "vs_4_0");
	g_vertexShader.m_inputLayout.createInputLayoutFromVertexShaderSignature(g_vertexShader.m_shaderBlob);

	g_pDeviceContext->IASetInputLayout(g_vertexShader.m_inputLayout.m_inputLayout);

	g_pixelShader.createFragmentShader(L"Tutorial07.fx", "PS", "ps_4_0");


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
	bd.ByteWidth = 480;//sizeof(SimpleVertex) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;

	g_pVertexBuffer.create(&bd, &InitData);

	// Set vertex buffer
	UINT stride = 20;// sizeof(SimpleVertex);
	UINT offset = 0;
	g_pDeviceContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer.m_buffer, &stride, &offset);

	// Create index buffer
	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;
	g_pIndexBuffer.create(&bd, &InitData);
	
	// Set index buffer
	g_pDeviceContext->IASetIndexBuffer(g_pIndexBuffer.m_buffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = 64;//sizeof(CBView);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	g_pCBView.create(&bd);

	bd.ByteWidth = 64;//sizeof(CBProj);
	g_pCBProj.create(&bd, nullptr);

	bd.ByteWidth = 80;//sizeof(CBWorld);
	g_pCBWorld.create(&bd, nullptr);

	// Load the Texture
	std::string path = "seafloor.dds";
	g_texture.loadFromFile(path);

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	g_pD3DDevice->CreateSamplerState(&sampDesc, &g_pSamplerState);
	
	// Initialize the world matrices
	g_World = rah::math::Identity4D();

	// Initialize the view matrix
	rah::Vector3D Eye(0.0f, 3.0f, -6.0f);
	rah::Vector3D At(0.0f, 1.0f, 0.0f);
	rah::Vector3D Up(0.0f, 1.0f, 0.0f);
	g_View = rah::math::LookAtLH(Eye, At, Up);

	CBView cbview;
	cbview.mView = rah::math::Transpose(g_View);
	g_pDeviceContext->UpdateSubresource(g_pCBView.m_buffer, 0, NULL, &cbview, 0, 0);

	// Initialize the projection matrix
	g_Projection = rah::math::PerspectiveFovLH(rah::math::PI / 4, SCREEN_WIDTH / SCREEN_HEIGHT, 0.01f, 100.0f);

	CBProj cbproj;
	cbproj.mProjection = rah::math::Transpose(g_Projection);
	g_pDeviceContext->UpdateSubresource(g_pCBProj.m_buffer, 0, NULL, &cbproj, 0, 0);

	g_pDeviceContext->OMSetRenderTargets(1, &g_renderTarget.m_renderTarget, g_pDepthStencilView);
	g_pDeviceContext->RSSetViewports(1, g_pViewport);
}

void render()
{
	// Update our time
	//static float t = 0.0f;
	//
	//static DWORD dwTimeStart = 0;
	//DWORD dwTimeCur = GetTickCount();
	//if (dwTimeStart == 0)
	//	dwTimeStart = dwTimeCur;
	//t = (dwTimeCur - dwTimeStart) / 1000.0f;
	

	// Rotate cube around the origin
	//g_World = XMMatrixRotationY(t);

	// Modify the color
	//g_Color.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
	//g_Color.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
	//g_Color.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	g_pDeviceContext->ClearRenderTargetView(g_renderTarget.m_renderTarget, ClearColor);

	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//
	// Update variables that change once per frame
	//
	CBWorld cb;
	cb.mWorld = rah::math::Transpose(g_World);
	cb.mColor = g_Color;
	g_pDeviceContext->UpdateSubresource(g_pCBWorld.m_buffer, 0, NULL, &cb, 0, 0);

	//
	// Render the cube
	//
	g_pDeviceContext->VSSetShader(g_vertexShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->VSSetConstantBuffers(0, 1, &g_pCBView.m_buffer);
	g_pDeviceContext->VSSetConstantBuffers(1, 1, &g_pCBProj.m_buffer);
	g_pDeviceContext->VSSetConstantBuffers(2, 1, &g_pCBWorld.m_buffer);

	g_pDeviceContext->PSSetShader(g_pixelShader.m_fragmentShader, NULL, 0);
	g_pDeviceContext->PSSetConstantBuffers(2, 1, &g_pCBWorld.m_buffer);
	g_pDeviceContext->PSSetShaderResources(0, 1, &g_texture.m_graphicTexture);
	g_pDeviceContext->PSSetSamplers(0, 1, &g_pSamplerState);

	g_pDeviceContext->DrawIndexed(36, 0, 0);

	//
	// Present our back buffer to our front buffer
	//
	g_pSwapChain->Present(0, 0);
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
		render();

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

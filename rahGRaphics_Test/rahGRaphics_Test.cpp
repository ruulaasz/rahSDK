#include "stdafx.h"
#include "rahGRaphics_Test.h"

#define MAX_LOADSTRING 100

// Variables globales:
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de t�tulo
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;
bool g_initialized = false;

ID3D11Device* g_pD3DDevice;
IDXGISwapChain* g_pSwapChain;
ID3D11DeviceContext* g_pDeviceContext;
ID3D11DepthStencilView* g_pDepthStencilView;
ID3D11SamplerState* g_pSamplerState;
D3D11_VIEWPORT* g_pViewport;

rah::Color g_backgroundColor(0.0f, 0.0f, 0.0f, 1.0f);
rah::Color g_shapesColor(0.8f, 0.0f, 0.0f, 1.0f);

float g_deltaTime = 0.0f;

rah::Matrix4D g_Scale;
rah::Matrix4D g_Translation;
rah::Matrix4D g_Rotation;

rah::VertexShader g_vertexModelShader;
rah::FragmentShader g_pixelModelShader;

rah::VertexShader g_vertexShapeShader;
rah::FragmentShader g_pixelShapeShader;

rah::CameraDebug g_camera;
rah::Model* g_Model;

rah::OBB g_OBB(rah::Vector3D(1, 2, 2), rah::Vector3D(1, 0.4f, 1), rah::Vector3D(30, 0, 0), rah::Vector3D(0, 0, 0), rah::Vector3D(0, 0, 0));
rah::OBB g_OBB1(rah::Vector3D(2, 2, 8), rah::Vector3D(0.5, 0.4f, 0.5), rah::Vector3D(30, 0, 0), rah::Vector3D(0, 0, 0), rah::Vector3D(0, 0, 0));
rah::AABB g_AABB(rah::Vector4D(1, 1, 4, 1.f), rah::Vector4D(-0.5f, -0.5f, -0.5f, 1.0f), rah::Vector4D(0.5f, 0.5f, 0.5f, 1.0f));
rah::Sphere g_sphere(1, rah::Vector3D(0, 0, 0));

rah::Ray g_Ray(rah::Vector3D(1, 2, 2), rah::Vector3D(1, 2, 5));

rah::Plane g_Plane(rah::Vector3D(1, 1, 1), 1.0f);


// Declaraciones de funciones adelantadas incluidas en este m�dulo de c�digo:
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

	rah::ResourceManagerInit resourceInit;
	resourceInit.Fabric = new rah::ResourceFabric();
	rah::ResourceManager::StartModule(resourceInit);

	rah::GStruct renderInit;
	rah::RenderManager::StartModule(renderInit);

	RAH_DEBUGER_MODULE_DECLARATION();

	g_pD3DDevice = reinterpret_cast<ID3D11Device*>(rah::GraphicManager::GetInstance().m_device.getPtr());
	g_pSwapChain = reinterpret_cast<IDXGISwapChain*>(rah::GraphicManager::GetInstance().m_swapchain.getPtr());
	g_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(rah::GraphicManager::GetInstance().m_deviceContext.getPtr());
	g_pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(rah::GraphicManager::GetInstance().m_depthStencilView.getPtr());
	g_pSamplerState = reinterpret_cast<ID3D11SamplerState*>(rah::GraphicManager::GetInstance().m_samplerState.getPtr());
	g_pViewport = reinterpret_cast<D3D11_VIEWPORT*>(rah::GraphicManager::GetInstance().m_viewport.getPtr());

	return RAH_SUCCESS;
}

void LoadGraphicResources()
{
	//load shaders
	g_vertexModelShader.createVertexShader(L"shaders.fx", "VS", "vs_5_0");
	g_vertexModelShader.m_inputLayout.createInputLayoutFromVertexShaderSignature(g_vertexModelShader.m_shaderBlob);
	g_pDeviceContext->IASetInputLayout(g_vertexModelShader.m_inputLayout.m_inputLayout);
	g_pixelModelShader.createFragmentShader(L"shaders.fx", "PS", "ps_5_0");

	g_vertexShapeShader.createVertexShader(L"shapes.fx", "VS", "vs_5_0");
	g_vertexShapeShader.m_inputLayout.createInputLayoutFromVertexShaderSignature(g_vertexShapeShader.m_shaderBlob);
	g_pDeviceContext->IASetInputLayout(g_vertexShapeShader.m_inputLayout.m_inputLayout);
	g_pixelShapeShader.createFragmentShader(L"shapes.fx", "PS", "ps_5_0");

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

	g_pDeviceContext->PSSetSamplers(0, 1, &g_pSamplerState);

	// Initialize the view matrix
	rah::Vector3D Eye(0.0f, 1.0f, -6.0f);
	rah::Vector3D At(0.0f, 1.0f, 0.0f);
	rah::Vector3D Up(0.0f, 1.0f, 0.0f);
	g_camera.PositionCamera(Eye, At, Up);

	rah::RenderManager::GetInstance().updateProjection();

	g_pDeviceContext->OMSetRenderTargets(1, &rah::GraphicManager::GetInstance().m_renderTarget.m_renderTarget, g_pDepthStencilView);
	g_pDeviceContext->OMSetDepthStencilState(rah::GraphicManager::GetInstance().m_depthStencilState, 1);
	
	g_pDeviceContext->RSSetViewports(1, g_pViewport);

	g_initialized = true;
}

void renderModels()
{
	// Update our time
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	g_deltaTime = (dwTimeCur - dwTimeStart) / 1000.0f;

	rah::GraphicManager::GetInstance().clearScreen(&rah::GraphicManager::GetInstance().m_renderTarget, g_backgroundColor);

	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	g_camera.Update();

	rah::RenderManager::GetInstance().updateView(rah::math::LookAtLH(g_camera.m_vPosition, g_camera.m_vView, g_camera.m_vUpVector));
	g_camera.m_frustum.calculateFrustum(rah::RenderManager::GetInstance().m_projection, rah::RenderManager::GetInstance().m_view);

	g_pDeviceContext->VSSetShader(g_vertexModelShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexModelShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelModelShader.m_fragmentShader, NULL, 0);

	// Update variables that change once per frame
	rah::RenderManager::GetInstance().updateWorld(rah::math::Identity4D());
	rah::RenderManager::GetInstance().updateColor(rah::Color(0.0f, 0.f, 0.2f));
	
	g_Model->render();

	g_pDeviceContext->VSSetShader(g_vertexShapeShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexShapeShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelShapeShader.m_fragmentShader, NULL, 0);

	rah::RenderManager::GetInstance().updateColor(g_shapesColor);

	rah::RenderManager::GetInstance().renderShape(g_sphere, 16);

	//// Update variables that change once per frame
	g_Scale = rah::math::ScalarMatrix4x4(g_OBB.m_dimentions.x, g_OBB.m_dimentions.y, g_OBB.m_dimentions.z);

	g_Rotation = rah::math::RotationMatrix4x4(rah::Degrees(g_OBB.m_axis[0].x).getRadians(), rah::math::Axis_X);
	g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(g_OBB.m_axis[1].y).getRadians(), rah::math::Axis_Y);
	g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(g_OBB.m_axis[2].z).getRadians(), rah::math::Axis_Z);

	g_Translation = rah::math::TranslationMatrix4x4(g_OBB.m_position.x, g_OBB.m_position.y, g_OBB.m_position.z);
	
	rah::RenderManager::GetInstance().updateWorld(g_Scale * g_Rotation * g_Translation);

	rah::RenderManager::GetInstance().renderShape(g_OBB);

	/*g_Scale = rah::math::ScalarMatrix4x4(g_AABB.m_max.x - g_AABB.m_min.x, g_AABB.m_max.y - g_AABB.m_min.y, g_AABB.m_max.z - g_AABB.m_min.z);

	g_Rotation = rah::math::Identity4D();

	g_Translation = rah::math::TranslationMatrix4x4(g_AABB.m_center.x, g_AABB.m_center.y, g_AABB.m_center.z);

	cbWorld.mWorld = g_Scale * g_Rotation * g_Translation;

	g_pDeviceContext->UpdateSubresource(g_pCBWorld.m_buffer, 0, NULL, &cbWorld, 0, 0);

	rah::RenderManager::GetInstance().renderShape(g_AABB);

	g_World = rah::math::Identity4D();
	cbWorld.mWorld = g_World;
	g_pDeviceContext->UpdateSubresource(g_pCBWorld.m_buffer, 0, NULL, &cbWorld, 0, 0);
	rah::RenderManager::GetInstance().renderShape(g_Ray);

	g_Scale = rah::math::ScalarMatrix4x4(100, 100, 100);

	g_Rotation = rah::math::Identity4D();

	g_Translation = rah::math::Identity4D();

	cbWorld.mWorld = g_Scale * g_Rotation * g_Translation;

	g_pDeviceContext->UpdateSubresource(g_pCBWorld.m_buffer, 0, NULL, &cbWorld, 0, 0);

	cbColor.mColor = rah::Color(0.5f, 0.5f, 0.5f);

	g_pDeviceContext->UpdateSubresource(g_pCBColor.m_buffer, 0, NULL, &cbColor, 0, 0);

	rah::RenderManager::GetInstance().renderGrid();*/

	// switch the back buffer and the front buffer
	g_pSwapChain->Present(0, 0);
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: colocar c�digo aqu�.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RAHGRAPHICS_TEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicializaci�n de la aplicaci�n:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RAHGRAPHICS_TEST));
	hAccelTable;
    MSG msg;

	InitD3D(g_hWnd);
	LoadGraphicResources();

	/************************************************************************/
	/* Prueba de inicializacion de recursos                                 */
	/************************************************************************/
	rah::BasicResourceParams* rParams = new rah::BasicResourceParams();
	rParams->filePath = "resources\\models\\Bassilisk\\Basillisk.dae";
	g_Model = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(rParams, rah::ResourceTypes::RAH_Model);

	while (TRUE)
	{
		// Check to see if any messages are waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);

			// check to see if it's time to quit
			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			renderModels();
		}
	}

	rah::GraphicManager::CloseModule();
	rah::RenderManager::CloseModule();
    return (int) msg.wParam;
}

//
//  FUNCI�N: MyRegisterClass()
//
//  PROP�SITO: registrar la clase de ventana.
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
//   FUNCI�N: InitInstance(HINSTANCE, int)
//
//   PROP�SITO: guardar el identificador de instancia y crear la ventana principal
//
//   COMENTARIOS:
//
//        En esta funci�n, se guarda el identificador de instancia en una variable com�n y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; // Almacenar identificador de instancia en una variable global

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  FUNCI�N: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROP�SITO:  procesar mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el men� de aplicaciones
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
            // Analizar las selecciones de men�:
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

	case WM_SIZE:
		{
			if (g_initialized)
			{
				rah::RenderManager::GetInstance().updateProjection();
			}
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			hdc;
            // TODO: Agregar cualquier c�digo de dibujo que use hDC aqu�...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(WM_QUIT);

		if (wParam == 0x57)
			g_camera.MoveCamera(0.5f);

		if (wParam == 0x53)
			g_camera.MoveCamera(-0.5f);

		if (wParam == 0x41)
			g_camera.StrafeCamera(0.5f);

		if (wParam == 0x44)
			g_camera.StrafeCamera(-0.5f);

		if (wParam == 0x5A)//Z
			g_camera.m_stopMoving = !g_camera.m_stopMoving;
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
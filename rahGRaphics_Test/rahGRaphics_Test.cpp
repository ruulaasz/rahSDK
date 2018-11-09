#include "stdafx.h"
#include "rahGRaphics_Test.h"
//#include <vld.h>
#define MAX_LOADSTRING 100

// Variables globales:
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;
bool g_initialized = false;

IDXGISwapChain* g_pSwapChain;
ID3D11DeviceContext* g_pDeviceContext;
ID3D11DepthStencilView* g_pDepthStencilView;

rah::Color g_backgroundColor(0.0f, 0.0f, 0.0f, 1.0f);
rah::Color g_shapesColor(rah::Color::green);

float g_deltaTime = 0.0f;

rah::VertexShader g_vertexModelShader;
rah::FragmentShader g_pixelModelShader;

rah::VertexShader g_vertexShapeShader;
rah::FragmentShader g_pixelShapeShader;

rah::CameraDebug g_camera;
rah::PlayerActor*  g_Actor;
rah::PlayerController* g_controller;
rah::World g_world;

float g_playerSpeed = 1.f;

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

	rah::ResourceManagerInit resourceInit;
	resourceInit.Fabric = new rah::ResourceFabric();
	rah::ResourceManager::StartModule(resourceInit);

	rah::GStruct renderInit;
	rah::RenderManager::StartModule(renderInit);

	RAH_DEBUGER_MODULE_DECLARATION();

	g_pSwapChain = reinterpret_cast<IDXGISwapChain*>(rah::GraphicManager::GetInstance().m_swapchain.getPtr());
	g_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(rah::GraphicManager::GetInstance().m_deviceContext.getPtr());
	g_pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(rah::GraphicManager::GetInstance().m_depthStencilView.getPtr());

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

	// Initialize the view matrix
	rah::Vector3D Eye(0.0f, 30.f, -8.0f);
	rah::Vector3D At(0.0f, 0.0f, 0.0f);
	rah::Vector3D Up(0.0f, 1.0f, 0.0f);
	g_camera.PositionCamera(Eye, At, Up);

	rah::RenderManager::GetInstance().updateProjection();

	g_pDeviceContext->OMSetRenderTargets(1, &rah::GraphicManager::GetInstance().m_renderTarget.m_renderTarget, g_pDepthStencilView);

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

	g_pDeviceContext->VSSetShader(g_vertexModelShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexModelShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelModelShader.m_fragmentShader, NULL, 0);

	// Update variables that change once per frame
	rah::RenderManager::GetInstance().updateWorld(rah::math::Identity4D());
	rah::RenderManager::GetInstance().updateColor(rah::Color(0.0f, 0.f, 0.2f));
	
	g_world.Render();

	g_pDeviceContext->VSSetShader(g_vertexShapeShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexShapeShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelShapeShader.m_fragmentShader, NULL, 0);

	rah::RenderManager::GetInstance().updateWorld(rah::math::Identity4D());
	rah::RenderManager::GetInstance().updateColor(rah::Color(0.0f, 0.f, 0.2f));

	rah::RenderManager::GetInstance().renderGrid(120);

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
	hAccelTable;
    MSG msg;

	InitD3D(g_hWnd);
	LoadGraphicResources();
	/************************************************************************/
	/* Prueba de inicializacion de recursos                                 */
	/************************************************************************/
	rah::SimpleActorInit* params = new rah::SimpleActorInit();
	params->_color = rah::Color();
	params->_nameModel = "resources\\models\\Bassilisk\\Basillisk.dae";
	params->_transform = rah::Transform(rah::Vector3D(0,0,0), rah::Vector3D(0, 0, 0), rah::Vector3D(1, 1, 1));
	g_Actor = new rah::PlayerActor();
	g_Actor->Initialize((void*)params);

	RAH_SAFE_DELETE(params);
	g_world.RegisterActor(g_Actor);

	g_controller = new rah::PlayerController();
	g_controller->AddPlayer(g_Actor);

	rah::MoveCommand* moveComand = new rah::MoveCommand();
	moveComand->axis = 2;
	moveComand->value = g_playerSpeed;
	g_controller->AddAction(0x57, WM_KEYDOWN, &rah::PlayerActor::Move, (void*)moveComand);

	rah::MoveCommand* moveComand1 = new rah::MoveCommand();
	moveComand1->axis = 2;
	moveComand1->value = g_playerSpeed  * -1;
	g_controller->AddAction(0x53, WM_KEYDOWN, &rah::PlayerActor::Move, (void*)moveComand1);

	rah::MoveCommand* moveComand2 = new rah::MoveCommand();
	moveComand2->axis = 1;
	moveComand2->value = g_playerSpeed * -1;
	g_controller->AddAction(0x41, WM_KEYDOWN, &rah::PlayerActor::Move, (void*)moveComand2);

	rah::MoveCommand* moveComand3 = new rah::MoveCommand();
	moveComand3->axis = 1;
	moveComand3->value = g_playerSpeed;
	g_controller->AddAction(0x44, WM_KEYDOWN, &rah::PlayerActor::Move, (void*)moveComand3);

	rah::InputManager::GetInstance().RegisterController(g_controller);

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
			g_camera.m_vView = g_Actor->m_transform.m_position;

			g_world.Update(g_deltaTime);
			renderModels();
		}
	}

	g_world.Destroy();
	rah::GraphicManager::CloseModule();
	rah::RenderManager::CloseModule();
	rah::InputManager::CloseModule();
	rah::ResourceManager::CloseModule();
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
	rah::InputManager::StartModule(NULL);

	g_hInst = hInstance; // Almacenar identificador de instancia en una variable global

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

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
	rah::InputEvent mainEvent;
	mainEvent.key = wParam;
	mainEvent.keyDown = message;
	rah::InputManager::GetInstance().CheckInput(&mainEvent);
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
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		//g_controller.CheckInput(&mainEvent);
		if (wParam == VK_ESCAPE)
			PostQuitMessage(WM_QUIT);

		if (wParam == 0x57)
		{
			//g_camera.MoveCamera(0.5f);
			//g_Actor.m_transform.m_position.z++;
			g_camera.m_vPosition.z += g_Actor->m_velocity.z;
		}
			
		if (wParam == 0x53)
		{
			//	g_camera.MoveCamera(-0.5f);
			//g_Actor.m_transform.m_position.z--;
			g_camera.m_vPosition.z -= g_Actor->m_velocity.z;
		}
		
		if (wParam == 0x41)
		{
			//g_camera.StrafeCamera(0.5f);
			//g_Actor.m_transform.m_position.x--;
			g_camera.m_vPosition.x -= g_Actor->m_velocity.x;
		}

		if (wParam == 0x44)
		{
			//g_camera.StrafeCamera(-0.5f);
			//g_Actor.m_transform.m_position.x++;
			g_camera.m_vPosition.x += g_Actor->m_velocity.x;
		}

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
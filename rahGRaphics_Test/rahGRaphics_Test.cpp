#include "stdafx.h"
#include "rahGRaphics_Test.h"

<<<<<<< HEAD
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <vld.h>
=======
//#include <vld.h>
>>>>>>> 4b01339104dc0e0d45f4d002b839698cc0ad4632

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

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
ID3D11Device* g_pDevice;

float g_deltaTime = 0.0f;

rah::VertexShader g_vertexModelShader;
rah::FragmentShader g_pixelModelShader;

rah::VertexShader g_vertexShapeShader;
rah::FragmentShader g_pixelShapeShader;

rah::Color g_backgroundColor;
rah::Color g_modelColor;

rah::CameraDebug g_camera;
rah::PlayerActor*  g_Actor;
rah::PlayerController* g_controller;

rah::World g_world;

rah::ResourceFabric* g_fabric;

float g_playerSpeed = 0.5f;
int g_gridDensity = 120;

rah::GraphicTexture* guiModelPrev = nullptr;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// this function initializes and prepares Direct3D for use
RahResult InitModules()
{
	RAH_DEBUGER_MODULE_DECLARATION();

	rah::InitStruct init;
	init.w = SCREEN_WIDTH;
	init.h = SCREEN_HEIGHT;

	rah::GraphicManager::StartModule(init);
	rah::GraphicManager::GetInstance().init(g_hWnd);

<<<<<<< HEAD
	g_fabric = new rah::ResourceFabric();
=======
	g_pSwapChain = reinterpret_cast<IDXGISwapChain*>(rah::GraphicManager::GetInstance().m_swapchain.getPtr());
	g_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(rah::GraphicManager::GetInstance().m_deviceContext.getPtr());
	g_pDevice = reinterpret_cast<ID3D11Device*>(rah::GraphicManager::GetInstance().m_device.getPtr());
	g_pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(rah::GraphicManager::GetInstance().m_depthStencilView.getPtr());

	rah::ImgManager::StartModule(NULL);

>>>>>>> 4b01339104dc0e0d45f4d002b839698cc0ad4632
	rah::ResourceManagerInit resourceInit;
	resourceInit.Fabric = g_fabric;
	rah::ResourceManager::StartModule(resourceInit);

	rah::GStruct renderInit;
	rah::RenderManager::StartModule(renderInit);

	rah::AudioManager::StartModule(NULL);

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
	rah::GraphicManager::GetInstance().clearScreen(&rah::GraphicManager::GetInstance().m_renderTarget, g_backgroundColor);

	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	g_camera.Update();

	g_pDeviceContext->VSSetShader(g_vertexModelShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexModelShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelModelShader.m_fragmentShader, NULL, 0);

	// Update variables that change once per frame
	rah::RenderManager::GetInstance().updateWorld(rah::math::Identity4D());
	rah::RenderManager::GetInstance().updateColor(g_modelColor);
	
	g_world.Render();

	g_pDeviceContext->VSSetShader(g_vertexShapeShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexShapeShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelShapeShader.m_fragmentShader, NULL, 0);

	rah::RenderManager::GetInstance().updateWorld(rah::math::Identity4D());

	rah::RenderManager::GetInstance().renderGrid(g_gridDensity);
}

void changePreview()
{
	rah::BasicResourceParams p;
	p.filePath = "resources\\models\\";
	p.filePath += g_Actor->m_model->m_name.Get();

	p.filePath.pop_back();
	p.filePath.pop_back();
	p.filePath.pop_back();
	p.filePath.pop_back();

	p.filePath += "\\";

	p.filePath += g_Actor->m_model->m_name.Get();

	p.filePath.pop_back();
	p.filePath.pop_back();
	p.filePath.pop_back();

	p.filePath += "dds";

	guiModelPrev = (rah::GraphicTexture*)rah::ResourceManager::GetInstance().LoadResource(&p, rah::ResourceTypes::RAH_GraphicTexture);
}

void changeModel(std::string _path)
{
	rah::Model* newModel = nullptr;

	rah::BasicResourceParams params;
	params.filePath = _path;

	newModel = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(&params, rah::ResourceTypes::RAH_Model);

	g_Actor->m_model = newModel;

	changePreview();
}

#define MAXMODELS 4

int current = 0;
std::string smodels[MAXMODELS] = { "resources\\models\\ManEater\\ManEater.dae", "resources\\models\\Basillisk\\Basillisk.dae", "resources\\models\\ManEater\\ManEater.dae", "resources\\models\\Basillisk\\Basillisk.dae"};


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

	InitModules();

	LoadGraphicResources();

	/************************************************************************/
	/* Prueba de inicializacion de recursos                                 */
	/************************************************************************/
	rah::SimpleActorInit* params = new rah::SimpleActorInit();
	params->_color = rah::Color();
	params->_nameModel = "resources\\models\\ManEater\\ManEater.dae";
	params->_transform = rah::Transform(rah::Vector3D(0,0,0), rah::Vector3D(0, 0, 0), rah::Vector3D(1, 1, 1));
	g_Actor = new rah::PlayerActor();
	g_Actor->Initialize((void*)params);

	g_world.RegisterActor(g_Actor);
	RAH_SAFE_DELETE(params);

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

	rah::rahAudioFile* audio;
	rah::AudioParams aprm;
	aprm.ChannelGroup = rah::AudioManager::GetInstance().ChannelName(rah::ChannelsTypesNames::MUSIC);
	aprm.filePath = "resources\\audio\\Gorillaz - Clint Eastwood (Official Video) (128  kbps).mp3";
	aprm.IsStream = false;
	aprm.Mode = rah::rahSoundMode::MODE_2D;
	audio = (rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&aprm, rah::ResourceTypes::RAH_Audio);

	int volume = 5;
	bool mute = false;
	// Our state
	ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
	static bool p_open = false;

	changePreview();

	float my_tex_w = 200;
	float my_tex_h = 200;

	while (TRUE)
	{
		// Update our time
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		g_deltaTime = (dwTimeCur - dwTimeStart) / 1000.0f;

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
			g_world.Update(g_deltaTime);

			g_camera.m_vView = g_Actor->m_transform.m_position;
			g_camera.m_vPosition = g_Actor->m_transform.m_position;
			g_camera.m_vPosition += rah::Vector3D(0.0f, 30.f, -8.0f);

			rah::ImgManager::GetInstance().update();
			
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("General");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("\nBackground Color");
				ImGui::ColorEdit3("current color", (float*)&clear_color); // Edit 3 floats representing a color
				g_backgroundColor = rah::Color(clear_color.x, clear_color.y, clear_color.z , 1.0f);

				ImGui::End();

				if (ImGui::BeginMainMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Edit"))
					{
						if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
						if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
						ImGui::Separator();
						if (ImGui::MenuItem("Cut", "CTRL+X")) {}
						if (ImGui::MenuItem("Copy", "CTRL+C")) {}
						if (ImGui::MenuItem("Paste", "CTRL+V")) {}
						ImGui::EndMenu();
					}

					ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

					ImGui::EndMainMenuBar();

					ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
					if (ImGui::Begin("World Entities", false, ImGuiWindowFlags_MenuBar))
					{
						// left
						static int selected = 0;
						ImGui::BeginChild("left pane", ImVec2(150, 0), true);
						for (int i = 0; i < g_world.m_actors.size(); i++)
						{
							char label[128];
							sprintf(label, "Actor %d", g_world.m_actors.at(i)->m_id);
							if (ImGui::Selectable(label, selected == i))
								selected = i;
						}
						ImGui::EndChild();
						ImGui::SameLine();

						// right
						ImGui::BeginGroup();
						ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
						ImGui::Text("Actor: %d", selected);
						ImGui::Separator();
						if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
						{
							for (int i = 0; i < g_world.m_actors.size(); i++)
							{
								
							}

							if (ImGui::BeginTabItem("Model"))
							{
								ImGui::Text("Current Model");
								ImGui::Image(guiModelPrev->m_graphicTexture, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
								if (ImGui::Button("Next"))
								{
									if (current < MAXMODELS - 1)
										current++;
									else
										current = 0;

									changeModel(smodels[current]);
								}
								if (ImGui::Button("Prev"))
								{
									if (current == 0)
										current = MAXMODELS - 1;
									else
										current--;

									changeModel(smodels[current]);
								}
								ImGui::EndTabItem();
							}
							if (ImGui::BeginTabItem("Details"))
							{
								ImGui::Text("ID: %d", g_world.m_actors.at(selected)->m_id);
								ImGui::EndTabItem();
							}

							ImGui::EndTabBar();
						}
						ImGui::EndChild();
						ImGui::EndGroup();
					}
					ImGui::End();

					ImGui::Begin("Audio");                          // Create a window called "Hello, world!" and append into it.

					if (ImGui::Button("Play"))
					{
						audio->Play();
					}
					if (ImGui::Button("Pause"))
					{
						audio->SetPaused(true);
					}
					if (ImGui::Button("Resume"))
					{
						audio->SetPaused(false);
					}

					if (ImGui::Checkbox("Mute", &mute))
					{
						audio->Mute(mute);
					}

					ImGui::SliderInt("Volume", &volume, 0, 10);
					audio->SetVolume(volume);

					ImGui::End();
				}
			}

			renderModels();
			rah::ImgManager::GetInstance().render();

			g_pSwapChain->Present(0, 0);
		}
	}

	g_world.Destroy();
	rah::GraphicManager::CloseModule();
	rah::RenderManager::CloseModule();
	rah::InputManager::CloseModule();
	rah::ResourceManager::CloseModule();
<<<<<<< HEAD
	rah::AudioManager::CloseModule();
	rah::debug::Debug::CloseModule();
	RAH_SAFE_DELETE(g_fabric);
=======
	rah::ImgManager::CloseModule();

>>>>>>> 4b01339104dc0e0d45f4d002b839698cc0ad4632
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

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

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

		if (wParam == 0x43)
		{
			changeModel("resources\\models\\Bassilisk\\Basillisk.dae");
			//g_camera.MoveCamera(0.5f);
			//g_Actor.m_transform.m_position.z++;
			//g_camera.m_vPosition.z += g_Actor->m_transform.m_position.z;
		}
			
		if (wParam == 0x53)
		{
			//	g_camera.MoveCamera(-0.5f);
			//g_Actor.m_transform.m_position.z--;
			//g_camera.m_vPosition.z -= g_Actor->m_transform.m_position.z;
		}
		
		if (wParam == 0x41)
		{
			//g_camera.StrafeCamera(0.5f);
			//g_Actor.m_transform.m_position.x--;
			//g_camera.m_vPosition.x -= g_Actor->m_transform.m_position.x;
		}

		if (wParam == 0x44)
		{
			//g_camera.StrafeCamera(-0.5f);
			//g_Actor.m_transform.m_position.x++;
			//g_camera.m_vPosition.x += g_Actor->m_transform.m_position.x;
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
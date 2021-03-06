#include "stdafx.h"
#include "rahGRaphics_Test.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <collision/q3Box.h>

//#include <vld.h>

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_LOADSTRING 100

// Variables globales:
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de t�tulo
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;
bool g_initialized = false;

IDXGISwapChain* g_pSwapChain;
ID3D11DeviceContext* g_pDeviceContext;
ID3D11DepthStencilView* g_pDepthStencilView;
ID3D11Device* g_pDevice;

float g_deltaTime = 0.1f;

rah::VertexShader g_vertexModelShader;
rah::FragmentShader g_pixelModelShader;

rah::VertexShader g_vertexShapeShader;
rah::FragmentShader g_pixelShapeShader;

rah::Color g_backgroundColor;

rah::CameraDebug g_camera;

rah::PlayerActor*  g_Actor;
rah::ModelComponent* g_ModelComponent;
rah::BoxComponent* g_BoxComponent;

rah::PlayerController* g_controller;

rah::World g_world;

rah::ResourceFabric* g_fabric;

rah::rahAudioFile* audio;

float g_playerSpeed = 0.5f;
int g_gridDensity = 120;

rah::GraphicTexture* guiModelPrev = nullptr;

std::vector<rah::PhysicBody*> g_physicBody;

rah::PhysicBody* g_playerBody;

// Declaraciones de funciones adelantadas incluidas en este m�dulo de c�digo:
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

	g_fabric = new rah::ResourceFabric();
	g_pSwapChain = reinterpret_cast<IDXGISwapChain*>(rah::GraphicManager::GetInstance().m_swapchain.getPtr());
	g_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(rah::GraphicManager::GetInstance().m_deviceContext.getPtr());
	g_pDevice = reinterpret_cast<ID3D11Device*>(rah::GraphicManager::GetInstance().m_device.getPtr());
	g_pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(rah::GraphicManager::GetInstance().m_depthStencilView.getPtr());

	rah::ImgManager::StartModule(NULL);

	rah::ResourceManagerInit resourceInit;
	resourceInit.Fabric = g_fabric;
	rah::ResourceManager::StartModule(resourceInit);

	rah::GStruct renderInit;
	rah::RenderManager::StartModule(renderInit);

	rah::AudioManager::StartModule(NULL);

	rah::ComponentFactory::StartModule(NULL);

	rah::DeferredManager::StartModule(NULL);

	rah::InitPhysic physicInit;
	physicInit.dt = 1.0f / 60.0f;
	physicInit.gravity = rah::Vector3D(0.0f, -9.8f);
	physicInit.paused = false;
	physicInit.iterations = 20;
	rah::PhysicManager::StartModule(physicInit);

	q3BodyDef bodyDef;
	rah::PhysicBody* body = rah::PhysicManager::GetInstance().CreateBody(bodyDef);
	g_physicBody.push_back(body);

	rah::PhysicManager::GetInstance().m_scene->SetEnableFriction(true);

	q3BoxDef boxDef;
	boxDef.SetRestitution(0);
	q3Transform tx;
	q3Identity(tx);
	boxDef.Set(tx, q3Vec3(50.0f, 1.0f, 50.0f));
	body->AddBox(boxDef);

	body = rah::PhysicManager::GetInstance().CreateBody(bodyDef);
	g_physicBody.push_back(body);

	boxDef;
	boxDef.SetRestitution(0);
	q3Identity(tx);
	//tx.position.x = 50.0f;
	tx.position.x = 25.0f;
	boxDef.Set(tx, q3Vec3(1.0f, 25.0f, 50.0f));
	body->AddBox(boxDef);

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

	rah::DeferredManager::GetInstance().setRenderTargets();

	g_initialized = true;
}

void renderWorld()
{
	rah::GraphicManager::GetInstance().clearScreen(&rah::GraphicManager::GetInstance().m_renderTarget, g_backgroundColor);

	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	g_camera.Update();

	g_pDeviceContext->VSSetShader(g_vertexModelShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexModelShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelModelShader.m_fragmentShader, NULL, 0);

	// Update variables that change once per frame
	rah::RenderManager::GetInstance().updateWorld(rah::math::Identity4D());
	
	g_world.Render();

	for (size_t i = 0; i < g_physicBody.size(); i++)
	{
		rah::AABB aabb = g_physicBody[i]->GetAABB();

		rah::RenderManager::GetInstance().renderShape(aabb, g_physicBody[i]->m_color);
	}

	g_pDeviceContext->VSSetShader(g_vertexShapeShader.m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexShapeShader.m_inputLayout.m_inputLayout);
	g_pDeviceContext->PSSetShader(g_pixelShapeShader.m_fragmentShader, NULL, 0);

	rah::RenderManager::GetInstance().updateWorld(rah::math::Identity4D());

	rah::RenderManager::GetInstance().renderGrid(g_gridDensity);
}

void changePreview()
{
	rah::ModelComponent* m = reinterpret_cast<rah::ModelComponent*>(g_Actor->getComponent("model"));

	rah::BasicResourceParams p;
	p.filePath = "resources\\models\\";
	p.filePath += m->m_model->m_name.Get();

	p.filePath.pop_back();
	p.filePath.pop_back();
	p.filePath.pop_back();
	p.filePath.pop_back();

	p.filePath += "\\";

	p.filePath += m->m_model->m_name.Get();

	p.filePath.pop_back();
	p.filePath.pop_back();
	p.filePath.pop_back();

	p.filePath += "dds";

	guiModelPrev = (rah::GraphicTexture*)rah::ResourceManager::GetInstance().LoadResource(&p, rah::ResourceTypes::RAH_GraphicTexture);
}

void changeModel(std::string _path)
{
	rah::ModelComponent* m = reinterpret_cast<rah::ModelComponent*>(g_Actor->getComponent("model"));
	rah::Model* newModel = nullptr;

	rah::BasicResourceParams params;
	params.filePath = _path;

	newModel = (rah::Model*)rah::ResourceManager::GetInstance().LoadResource(&params, rah::ResourceTypes::RAH_Model);

	m->m_model = newModel;

	changePreview();
}

#define MAXMODELS 4

int current = 0;
std::string smodels[MAXMODELS] = { "resources\\models\\ManEater\\ManEater.dae", "resources\\models\\Basillisk\\Basillisk.dae", "resources\\models\\ManEater\\ManEater.dae", "resources\\models\\Basillisk\\Basillisk.dae"};

// Our state
ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
float my_tex_w = 200;
float my_tex_h = 200;

void GUI()
{
	ImGui::Begin("General");                         

	ImGui::Text("\nBackground Color");
	ImGui::ColorEdit3("current color", (float*)&clear_color); // Edit 3 floats representing a color
	g_backgroundColor = rah::Color(clear_color.x, clear_color.y, clear_color.z, 1.0f);

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
					if (rah::DeferredManager::GetInstance().pRenderTargets[0])
					{
						//ID3D11Device::CreateShaderResourceView()
						ID3D11ShaderResourceView * test;
						HRESULT error = g_pDevice->CreateShaderResourceView(rah::DeferredManager::GetInstance().m_renderTexture[1].m_texture, NULL, &test);

						if(error == S_OK)
						{
							DirectX::ScratchImage image;
							HRESULT hr = CaptureTexture(g_pDevice, g_pDeviceContext, rah::DeferredManager::GetInstance().m_renderTexture[1].m_texture, image);
							if (SUCCEEDED(hr))
							{
								/*hr = SaveToDDSFile(image.GetImages(),
									image.GetImageCount(), image.GetMetadata(),
									DirectX::DDS_FLAGS_NONE, L"caca.dds");*/
							}
							//DirectX::CreateShaderResourceView(g_pDevice, );
							ImGui::Image(test, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
						}
					}

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
					ImGui::Text("\nactor transform x: %f", g_Actor->m_transform.m_position.x);
					ImGui::Text("actor transform y: %f", g_Actor->m_transform.m_position.y);
					ImGui::Text("actor transform z: %f", g_Actor->m_transform.m_position.z);

					ImGui::Text("\nmodel transform x: %f", reinterpret_cast<rah::ModelComponent*>(g_Actor->getComponent("model"))->m_model->m_transform.Line[0][3]);
					ImGui::Text("model transform y: %f", reinterpret_cast<rah::ModelComponent*>(g_Actor->getComponent("model"))->m_model->m_transform.Line[1][3]);
					ImGui::Text("model transform z: %f", reinterpret_cast<rah::ModelComponent*>(g_Actor->getComponent("model"))->m_model->m_transform.Line[2][3]);

					ImGui::Text("\nbox transform x: %f", reinterpret_cast<rah::BoxComponent*>(g_Actor->getComponent("box"))->m_box.m_center.x);
					ImGui::Text("box transform y: %f", reinterpret_cast<rah::BoxComponent*>(g_Actor->getComponent("box"))->m_box.m_center.y);
					ImGui::Text("box transform z: %f", reinterpret_cast<rah::BoxComponent*>(g_Actor->getComponent("box"))->m_box.m_center.z);

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::EndChild();
			ImGui::EndGroup();
		}
		ImGui::End();
	}
}

void inputs()
{
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

	InitModules();

	LoadGraphicResources();

	/************************************************************************/
	/* Prueba de inicializacion de recursos                                 */
	/************************************************************************/
	rah::SimpleActorInit* params = new rah::SimpleActorInit();
	params->_transform = rah::Transform(rah::Vector3D(0,0,0), rah::Vector3D(0, 0, 0), rah::Vector3D(1, 1, 1));
	g_Actor = new rah::PlayerActor();

	g_Actor->Initialize((void*)params);

	g_Actor->addComponent(rah::ComponentFactory::GetInstance().createEmptyComponent(g_Actor, rah::CT_MODEL, "model"));
	g_Actor->addComponent(rah::ComponentFactory::GetInstance().createEmptyComponent(g_Actor, rah::CT_BOX, "box"));
	g_Actor->addComponent(rah::ComponentFactory::GetInstance().createEmptyComponent(g_Actor, rah::CT_LISTENER, "listener"));
	g_Actor->addComponent(rah::ComponentFactory::GetInstance().createEmptyComponent(g_Actor, rah::CT_AUDIO, "audio"));

	reinterpret_cast<rah::BoxComponent*>(g_Actor->getComponent("box"))->assignModel(reinterpret_cast<rah::ModelComponent*>(g_Actor->getComponent("model")));

	g_world.RegisterActor(g_Actor);
	RAH_SAFE_DELETE(params);

	inputs();

	changePreview();

	q3BodyDef bodyDef;
	bodyDef.position.Set(g_Actor->m_transform.m_position.x, g_Actor->m_transform.m_position.y, g_Actor->m_transform.m_position.z);
	bodyDef.axis.Set(g_Actor->m_transform.m_rotation.x, g_Actor->m_transform.m_rotation.y, g_Actor->m_transform.m_rotation.z);
	bodyDef.bodyType = eDynamicBody;
	
	g_playerBody = rah::PhysicManager::GetInstance().CreateBody(bodyDef);

	g_physicBody.push_back(g_playerBody);

	q3Transform tx;
	q3Identity(tx);
	tx.position.x = g_Actor->m_transform.m_position.x;
	tx.position.y = g_Actor->m_transform.m_position.y;
	tx.position.z = g_Actor->m_transform.m_position.z;
	q3BoxDef boxDef;
	boxDef.SetDensity(1.f);
	boxDef.SetFriction(0.4f);
	rah::BoxComponent* box = (rah::BoxComponent*)g_Actor->getComponent("box");
	boxDef.Set(tx, q3Vec3(rah::math::Abs(box->m_box.m_max.x) + rah::math::Abs(box->m_box.m_min.x), rah::math::Abs(box->m_box.m_max.y) + rah::math::Abs(box->m_box.m_min.y), rah::math::Abs(box->m_box.m_max.z) + rah::math::Abs(box->m_box.m_min.z)));
	g_playerBody->AddBox(boxDef);

	rah::AudioParams aprm;
	aprm.ChannelGroup = rah::AudioManager::GetInstance().ChannelName(rah::ChannelsTypesNames::MUSIC);
	aprm.filePath = "resources\\audio\\Gorillaz - Clint Eastwood (Official Video) (128  kbps).mp3";
	aprm.IsStream = false;
	aprm.Mode = rah::rahSoundMode::MODE_3D;
	audio = (rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&aprm, rah::ResourceTypes::RAH_Audio);
	audio->UpdatePositionVelocity(rah::Vector3D(0.0f, 0.0f), rah::Vector3D(0.0f));
	audio->m_channel->m_channel->set3DLevel(0.2);
	//audio->Set3DMinMaxDistance(0.0f, 10.0f);

	while (TRUE)
	{
		// Update our time
		//g_SartTime = ImGui::GetIO().DeltaTime;
		
		//g_deltaTime = (FinalTime - SartTime) / 1000.0f;

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
			
			rah::AudioManager::GetInstance().Update();

			rah::PhysicManager::GetInstance().Update(g_deltaTime);

			static float acc;

			acc += rah::PhysicManager::GetInstance().m_dt;
			static bool oncedo = true;
			if (acc > 1.0f && oncedo)
			{
				acc = 0;

				q3BodyDef bodyDef;
				bodyDef.position.Set(0.0f, 3.0f, 0.0f);
				bodyDef.axis.Set(q3RandomFloat(-1.0f, 1.0f), q3RandomFloat(-1.0f, 1.0f), q3RandomFloat(-1.0f, 1.0f));
				bodyDef.angle = q3PI * q3RandomFloat(-1.0f, 1.0f);
				bodyDef.bodyType = eDynamicBody;
				bodyDef.angularVelocity.Set(q3RandomFloat(1.0f, 3.0f), q3RandomFloat(1.0f, 3.0f), q3RandomFloat(1.0f, 3.0f));
				bodyDef.angularVelocity *= q3Sign(q3RandomFloat(-1.0f, 1.0f));
				bodyDef.linearVelocity.Set(q3RandomFloat(1.0f, 3.0f), q3RandomFloat(1.0f, 3.0f), q3RandomFloat(1.0f, 3.0f));
				bodyDef.linearVelocity *= q3Sign(q3RandomFloat(-1.0f, 1.0f));
				rah::PhysicBody* body = rah::PhysicManager::GetInstance().CreateBody(bodyDef);

				g_physicBody.push_back(body);

				q3Transform tx;
				q3Identity(tx);
				q3BoxDef boxDef;
				boxDef.Set(tx, q3Vec3(1.0f, 1.0f, 1.0f));
				body->AddBox(boxDef);
				oncedo = false;
			}
			g_Actor->m_transform.m_position.x = g_playerBody->m_body->GetTransform().position.x;
			g_Actor->m_transform.m_position.y = g_playerBody->m_body->GetTransform().position.y;
			g_Actor->m_transform.m_position.z = g_playerBody->m_body->GetTransform().position.z;
			for (int i = 3; i < g_physicBody.size(); i++)
			{
				q3AABB aabb;
				q3Transform world = q3Mul(g_physicBody[i]->m_body->GetTransform(), g_physicBody[i]->m_box->local);
				q3Vec3 v[8] = {
					q3Vec3(-g_physicBody[i]->m_box->e.x, -g_physicBody[i]->m_box->e.y, -g_physicBody[i]->m_box->e.z),
					q3Vec3(-g_physicBody[i]->m_box->e.x, -g_physicBody[i]->m_box->e.y,  g_physicBody[i]->m_box->e.z),
					q3Vec3(-g_physicBody[i]->m_box->e.x,  g_physicBody[i]->m_box->e.y, -g_physicBody[i]->m_box->e.z),
					q3Vec3(-g_physicBody[i]->m_box->e.x,  g_physicBody[i]->m_box->e.y,  g_physicBody[i]->m_box->e.z),
					q3Vec3(g_physicBody[i]->m_box->e.x, -g_physicBody[i]->m_box->e.y, -g_physicBody[i]->m_box->e.z),
					q3Vec3(g_physicBody[i]->m_box->e.x, -g_physicBody[i]->m_box->e.y,  g_physicBody[i]->m_box->e.z),
					q3Vec3(g_physicBody[i]->m_box->e.x,  g_physicBody[i]->m_box->e.y, -g_physicBody[i]->m_box->e.z),
					q3Vec3(g_physicBody[i]->m_box->e.x,  g_physicBody[i]->m_box->e.y,  g_physicBody[i]->m_box->e.z)
				};
				for (i32 i = 0; i < 8; ++i)
					v[i] = q3Mul(world, v[i]);

				q3Vec3 min = q3Vec3(Q3_R32_MAX, Q3_R32_MAX, Q3_R32_MAX);
				q3Vec3 max = q3Vec3(-Q3_R32_MAX, -Q3_R32_MAX, -Q3_R32_MAX);

				for (i32 i = 0; i < 8; ++i)
				{
					min = q3Min(min, v[i]);
					max = q3Max(max, v[i]);
				}

				aabb.min = min;
				aabb.max = max;
				rah::PhysicManager::GetInstance().m_scene->QueryAABB(g_physicBody[i], aabb);
			}
			q3AABB aabb;
			q3Transform world = q3Mul(g_playerBody->m_body->GetTransform(), g_playerBody->m_box->local);
			q3Vec3 v[8] = {
				q3Vec3(-g_playerBody->m_box->e.x, -g_playerBody->m_box->e.y, -g_playerBody->m_box->e.z),
				q3Vec3(-g_playerBody->m_box->e.x, -g_playerBody->m_box->e.y,  g_playerBody->m_box->e.z),
				q3Vec3(-g_playerBody->m_box->e.x,  g_playerBody->m_box->e.y, -g_playerBody->m_box->e.z),
				q3Vec3(-g_playerBody->m_box->e.x,  g_playerBody->m_box->e.y,  g_playerBody->m_box->e.z),
				q3Vec3(g_playerBody->m_box->e.x, -g_playerBody->m_box->e.y, -g_playerBody->m_box->e.z),
				q3Vec3(g_playerBody->m_box->e.x, -g_playerBody->m_box->e.y,  g_playerBody->m_box->e.z),
				q3Vec3(g_playerBody->m_box->e.x,  g_playerBody->m_box->e.y, -g_playerBody->m_box->e.z),
				q3Vec3(g_playerBody->m_box->e.x,  g_playerBody->m_box->e.y,  g_playerBody->m_box->e.z)
			};
			for (i32 i = 0; i < 8; ++i)
				v[i] = q3Mul(world, v[i]);

			q3Vec3 min = q3Vec3(Q3_R32_MAX, Q3_R32_MAX, Q3_R32_MAX);
			q3Vec3 max = q3Vec3(-Q3_R32_MAX, -Q3_R32_MAX, -Q3_R32_MAX);

			for (i32 i = 0; i < 8; ++i)
			{
				min = q3Min(min, v[i]);
				max = q3Max(max, v[i]);
			}

			aabb.min = min;
			aabb.max = max;
			//for (int i = 3; i < g_physicBody.size(); i++)
			//{
				rah::PhysicManager::GetInstance().m_scene->QueryAABB(g_playerBody, aabb);
			//}
			GUI();

			renderWorld();
			rah::ImgManager::GetInstance().render();

			g_pSwapChain->Present(0, 0);
		}

		g_deltaTime = ImGui::GetIO().DeltaTime;
	}

	g_world.Destroy();
	rah::GraphicManager::CloseModule();
	rah::RenderManager::CloseModule();
	rah::InputManager::CloseModule();
	rah::ResourceManager::CloseModule();
	rah::AudioManager::CloseModule();
	rah::debug::Debug::CloseModule();
	RAH_SAFE_DELETE(g_fabric);
	rah::ImgManager::CloseModule();
	rah::ComponentFactory::CloseModule();
	rah::DeferredManager::CloseModule();
	rah::PhysicManager::CloseModule();

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
	//rah::InputManager::GetInstance().CheckInput(&mainEvent);

	if (g_playerBody != NULL && g_Actor != NULL && rah::InputManager::GetInstance().CheckInput(&mainEvent) == RahResult::RAH_SUCCESS)
	{
		rah::Vector3D direction;
		if (wParam == 0x57)
		{
			direction.z += 10.f;
		}
		else if (wParam == 0x53)
		{
			direction.z -= 10.f;
		}
		else if (wParam == 0x41)
		{
			direction.x -= 10.f;
		}
		else if (wParam == 0x44)
		{
			direction.x += 10.f;
		}
		//direction += g_Actor->m_transform.m_position;
		//g_playerBody->SetTransform(g_Actor->m_transform);
		//direction.y = g_Actor->m_transform.m_position.y;
		//g_playerBody->m_body->SetToAwake();
		g_playerBody->SetLinearVelocity(direction);
		/*if(g_physicBody.size() >= 4)
			g_physicBody[3]->SetLinearVelocity(direction);*/
		//g_playerBody->m_body->ApplyLinearImpulseAtWorldPoint(q3Vec3(direction.x,direction.y,direction.z), q3Vec3(g_Actor->m_transform.m_position.x, g_Actor->m_transform.m_position.y, g_Actor->m_transform.m_position.z));
	}
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
		//g_controller.CheckInput(&mainEvent);
		if (wParam == VK_ESCAPE)
			PostQuitMessage(WM_QUIT);

		if (wParam == 0x43)
		{
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
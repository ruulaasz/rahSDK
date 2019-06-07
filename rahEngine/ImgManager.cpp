#include "ImgManager.h"

namespace rah
{
	RahResult ImgManager::Initialize(void * _init)
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_Init(rah::GraphicManager::GetInstance().m_hWnd);
		ImGui_ImplDX11_Init(reinterpret_cast<ID3D11Device*>(rah::GraphicManager::GetInstance().m_device.getPtr()), reinterpret_cast<ID3D11DeviceContext*>(rah::GraphicManager::GetInstance().m_deviceContext.getPtr()));

		return RahResult();
	}

	void ImgManager::Release()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void ImgManager::render()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void ImgManager::update()
	{
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	ImgManager::ImgManager()
	{

	}

	ImgManager::~ImgManager()
	{

	}
}
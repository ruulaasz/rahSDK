#include "ImgManager.h"
#include "rahEngine.h"

namespace rah
{
	RahResult ImgManager::Initialize(void * /*_init*/)
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

	void ImgManager::boxComponentGUI(Component* _component)
	{
		BoxComponent* box = reinterpret_cast<BoxComponent*>(_component);
		ImVec4 clear_color = ImVec4(box->m_color.r, box->m_color.g, box->m_color.b, 1.00f);

		ImGui::Begin("AABB");                     

		ImGui::Checkbox("Render", &box->m_rendereable);
		ImGui::Spacing();

		ImGui::Text("Box Color");
		ImGui::ColorEdit3("current color", (float*)&clear_color);
		box->m_color = rah::Color(clear_color.x, clear_color.y, clear_color.z, 1.0f);
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		bool adjust = box->m_adjustToModel;
		ImGui::Checkbox("Adjust to Model", &box->m_adjustToModel);
		ImGui::SameLine();
		ImGui::Text("Current Model: ");
		ImGui::SameLine();
		ImGui::Text(box->m_model->m_id.c_str());
		if (adjust != box->m_adjustToModel)
		{
			box->adjustBoxtoModel();
		}
		ImGui::Spacing();

		if (ImGui::CollapsingHeader("Box Transform"))
		{
			holdArrows("Offset Center X", box->m_offsetTransform.m_position.x, '0', 0.5f);
			holdArrows("Offset Center Y", box->m_offsetTransform.m_position.y, '1', 0.5f);
			holdArrows("Offset Center Z", box->m_offsetTransform.m_position.z, '2', 0.5f);

			float c[3] = { box->m_offsetTransform.m_position.x , box->m_offsetTransform.m_position.y, box->m_offsetTransform.m_position.z };
			ImGui::InputFloat3("Offset Center", c);
			box->m_offsetTransform.m_position.x = c[0];
			box->m_offsetTransform.m_position.y = c[1];
			box->m_offsetTransform.m_position.z = c[2];
			ImGui::Spacing();

			holdArrows("Offset Scale X", box->m_offsetTransform.m_scale.x, '3', 0.5f);
			holdArrows("Offset Scale Y", box->m_offsetTransform.m_scale.y, '4', 0.5f);
			holdArrows("Offset Scale Z", box->m_offsetTransform.m_scale.z, '5', 0.5f);

			float s[3] = { box->m_offsetTransform.m_scale.x , box->m_offsetTransform.m_scale.y, box->m_offsetTransform.m_scale.z };
			ImGui::InputFloat3("Offset Scale", s);
			box->m_offsetTransform.m_scale.x = s[0];
			box->m_offsetTransform.m_scale.y = s[1];
			box->m_offsetTransform.m_scale.z = s[2];
		}

		ImGui::End();
	}

	void ImgManager::modelComponentGUI(Component * _component)
	{
		ModelComponent* model = reinterpret_cast<ModelComponent*>(_component);
		ImVec4 clear_color = ImVec4(model->m_color.r, model->m_color.g, model->m_color.b, 1.00f);

		ImGui::Begin("Model");

		ImGui::Checkbox("Render", &model->m_rendereable);
		ImGui::Spacing();

		ImGui::Text("Model Color");
		ImGui::ColorEdit3("current color", (float*)&clear_color);
		model->m_color = rah::Color(clear_color.x, clear_color.y, clear_color.z, 1.0f);
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		
		if (ImGui::Button("change model"))
		{
			char filename[MAX_PATH];

			OPENFILENAME ofn;
			ZeroMemory(&filename, sizeof(filename));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
			ofn.lpstrFilter = "Any File\0*.*\0";
			ofn.lpstrFile = filename;
			ofn.lpstrInitialDir = "..\resources\models";
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Select a Model";
			ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

			if (GetOpenFileNameA(&ofn))
			{
				model->changeModel(filename);
			}
		}

		ImGui::End();
	}

	void ImgManager::audioComponentGUI(Component * _component)
	{
		ImGui::Begin("Audio");                          // Create a window called "Hello, world!" and append into it.

		AudioComponent* audio = reinterpret_cast<AudioComponent*>(_component);

		if (ImGui::Button("Add audio"))
		{
			char filename[MAX_PATH];

			OPENFILENAME ofn;
			ZeroMemory(&filename, sizeof(filename));
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
			ofn.lpstrFilter = "Any File\0*.*\0";
			ofn.lpstrFile = filename;
			ofn.lpstrInitialDir = "..\resources\audio";
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrTitle = "Select a Audio";
			ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

			if (GetOpenFileNameA(&ofn))
			{
				rah::AudioParams params;
				params.ChannelGroup = rah::AudioManager::GetInstance().ChannelName(rah::ChannelsTypesNames::DEFAULT);
				params.filePath = filename;
				params.IsStream = false;
				params.Mode = rah::rahSoundMode::MODE_3D;

				audio->addAudioFile(params);
				audio->m_audio.at(1)->m_volume = 1;
			}
		}
		ImGui::Spacing();

		for (size_t i = 0; i < audio->m_audioNumber; i++)
		{
			ImGui::PushID(i);
			ImGui::Separator();
			if (ImGui::Button("Play"))
			{
				audio->m_audio.at(i)->Play();
			}
			ImGui::Spacing();
			ImGui::PopID();

			ImGui::PushID(i);
			if (ImGui::Button("Pause"))
			{
				audio->m_audio.at(i)->SetPaused(true);
			}
			ImGui::Spacing();
			ImGui::PopID();

			ImGui::PushID(i);
			if (ImGui::Button("Resume"))
			{
				audio->m_audio.at(i)->SetPaused(false);
			}
			ImGui::Spacing();
			ImGui::PopID();

			ImGui::PushID(i);
			if (ImGui::Checkbox("Mute", &audio->m_mute))
			{
				audio->m_audio.at(i)->Mute(audio->m_mute);
			}
			ImGui::Spacing();
			ImGui::PopID();

			ImGui::PushID(i);
			ImGui::SliderInt("Volume", &audio->m_audio.at(i)->m_volume, 0, 10);
			audio->m_audio.at(i)->SetVolume(audio->m_audio.at(i)->m_volume);
			ImGui::Separator();
			ImGui::PopID();
		}

		ImGui::End();
	}

	void ImgManager::holdArrows(const char* _text, float& _f, char _id, float _steps)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::Text(_text);
		ImGui::SameLine();

		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);

		std::string name = std::string("L");
		name.push_back(_id);

		if (ImGui::ArrowButton(name.c_str(), ImGuiDir_Left))
		{ 
			_f -= _steps;
		}

		ImGui::SameLine(0.0f, spacing);
		name = std::string("R");
		name.push_back(_id);
	
		if (ImGui::ArrowButton(name.c_str(), ImGuiDir_Right))
		{ 
			_f += _steps;
		}

		ImGui::PopButtonRepeat();
	}
}
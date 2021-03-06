#pragma once

#include "rahAll.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

namespace rah
{
	class Component;

	class ImgManager : public Module<ImgManager, void*>
	{
	public:
		RahResult Initialize(void* _init);
		void Release();

		void render();
		void update();

		ImgManager();
		~ImgManager();

		void boxComponentGUI(Component* _component);
		void modelComponentGUI(Component* _component);
		void audioComponentGUI(Component* _component);

		void holdArrows(const char* _text, float& _f, char _id, float _steps = 1.f);
	};
}
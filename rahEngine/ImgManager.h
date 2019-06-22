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
	};
}
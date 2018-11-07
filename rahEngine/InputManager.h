#pragma once
#include "rahAll.h"
#include "Controller.h"
#include "InputEvent.h"
#include <vector>
namespace rah
{
	class InputManager : public Module<InputManager, void*>
	{
	protected:
		std::vector<Controller*> m_controllers;
	public:
		RahResult Initialize(void* _init);
		RahResult RegisterController(Controller* _controller);
		void Release();
		RahResult CheckInput(InputEvent* _event);
		InputManager();
		~InputManager();
	};
}

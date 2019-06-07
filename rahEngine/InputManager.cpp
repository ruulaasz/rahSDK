#include "InputManager.h"


namespace rah
{
	RahResult InputManager::Initialize(void * /*_init*/)
	{
		m_controllers.clear();
		return RAH_SUCCESS;
	}
	RahResult InputManager::RegisterController(Controller * _controller)
	{
		if (_controller == NULL)
		{
			GetLastError() = RAH_PARAM_IS_NULL;
			return RAH_PARAM_IS_NULL;
		}

		m_controllers.push_back(_controller);
		GetLastError() = RAH_SUCCESS;
		return RAH_SUCCESS;
	}
	void InputManager::Release()
	{
		for (size_t i = 0; i < m_controllers.size(); i++)
		{
			m_controllers[i]->Destroy();
			RAH_SAFE_DELETE(m_controllers[i]);
		}
		m_controllers.clear();
	}
	RahResult InputManager::CheckInput(InputEvent * _event)
	{
		for (size_t i = 0; i < m_controllers.size(); i++)
		{
			if (m_controllers[i]->CheckInput(_event) != RAH_DONT_FIND_KEY)
				GetLastError() = RAH_SUCCESS;
		}
		GetLastError() = RAH_DONT_FIND_KEY;
		return RAH_DONT_FIND_KEY;
	}
	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}
}
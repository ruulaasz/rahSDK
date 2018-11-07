#include "PlayerController.h"
#include "PlayerActor.h"

namespace rah
{
	RahResult PlayerController::AddPlayer(PlayerActor * _player)
	{
		if (m_player != NULL)
			return RAH_IS_PLAYER_ALREADY_ASSIGNED;

		if (_player == NULL)
			return RAH_PARAM_IS_NULL;

		m_player = _player;

		return RAH_SUCCESS;
	}
	RahResult PlayerController::AddAction(ActionInfo* _info)
	{
		if (RAH_SUCCESS != CheckForExistingInput(_info->input.key))
			return RAH_KEY_ALREADY_ASSIGNED;

		m_ActionInfo.push_back(_info);

		return RAH_SUCCESS;
	}
	RahResult PlayerController::AddAction(unsigned int _key, unsigned int _keyDown, void(PlayerActor::*_fuction)(void*), void* value)
	{
		ActionInfo* info = new ActionInfo();
		info->input.key = _key;
		info->input.keyDown = _keyDown;
		info->input.value = value;
		info->PFunction = _fuction;
		if (AddAction(info) != RAH_SUCCESS)
		{
			RAH_SAFE_DELETE(info);
			return RAH_KEY_ALREADY_ASSIGNED;
		}
		return RAH_SUCCESS;
	}
	RahResult PlayerController::CheckForExistingInput(unsigned int _key)
	{
		for (int i = 0; i < m_ActionInfo.size(); i++)
		{
			if (m_ActionInfo[i]->input.key == _key)
				return RAH_KEY_ALREADY_ASSIGNED;
		}
		return RAH_SUCCESS;
	}
	RahResult PlayerController::CheckInput(InputEvent * _event)
	{
		for (int i = 0; i < m_ActionInfo.size(); i++)
		{
			ActionInfo* info = m_ActionInfo[i];
			if (info->input.key == _event->key && info->input.keyDown == _event->keyDown)
			{
				(*m_player.*info->PFunction)((void*)info->input.value);
				return RAH_SUCCESS;
			}
		}
		return RAH_DONT_FIND_KEY;
	}
	void PlayerController::Destroy()
	{
		for (size_t i = 0; i < m_ActionInfo.size(); i++)
		{
			RAH_SAFE_DELETE(m_ActionInfo[i]->input.value);
			RAH_SAFE_DELETE(m_ActionInfo[i]);
		}
		m_ActionInfo.clear();
		m_player = NULL;
	}
	PlayerController::PlayerController()
	{
	}


	PlayerController::~PlayerController()
	{
	}
}

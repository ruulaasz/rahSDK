#pragma once
#include "Controller.h"
#include "InputEvent.h"
#include "PlayerActor.h"
#include <vector>

namespace rah
{
	//class PlayerActor;
	class PlayerController : public Controller
	{
	public:
		struct ActionInfo
		{
			InputEvent input;
			void(PlayerActor::*PFunction)(void*);
		};
#define AIIterator std::vector<ActionInfo*>::iterator
#define AIVector std::vector<ActionInfo*> 
	protected:
		AIVector m_ActionInfo;
		PlayerActor* m_player;
	public:
		virtual RahResult AddPlayer(PlayerActor* _player);
		virtual RahResult AddAction(ActionInfo* _info);
		virtual RahResult AddAction(unsigned int _key, unsigned int _keyDown, void(PlayerActor::*_fuction)(void*), void* value = NULL);
		virtual RahResult CheckInput(InputEvent* _event);
		virtual void Destroy();
	protected:
		virtual RahResult CheckForExistingInput(unsigned int _key);
	public:
		PlayerController();
		virtual ~PlayerController();
	};
}

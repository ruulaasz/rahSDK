#pragma once
#include "rahAll.h"
#include "InputEvent.h"

namespace rah
{
	class Controller
	{
	public:
		virtual RahResult CheckInput(InputEvent* _event) = 0;
		virtual void Destroy() = 0;
	public:
		Controller();
		virtual ~Controller();
	};
}

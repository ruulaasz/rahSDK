#pragma once
#include <fmod.hpp>

namespace rah
{
	class rahChannel
	{
	public:
		FMOD::Channel* m_channel;
		rahChannel();
		~rahChannel();
	};
}

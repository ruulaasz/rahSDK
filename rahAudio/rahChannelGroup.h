#pragma once
#include <fmod.hpp>
#include <string>

namespace rah
{
	class rahChannelGroup
	{
	public:
		rahChannelGroup();
		~rahChannelGroup();

		FMOD::ChannelGroup*  m_ChannelGroup;
		std::string m_Name;

		void SetPaused(bool _Paused);			
		void Stop();							
		void SetVolume(float _Volume);			
		void SetPitch(float _Pitch);			
		void Mute(bool _mute);													
		void AddGroup(rahChannelGroup* _Group);	
	};
}

#pragma once
#include <rahTools.h>
#include <fmod.hpp>
#include <fmod_common.h>
#include "rahChannelGroup.h"
#include "rahAudioFile.h"

#define MAX_CHANNELS 100
#define DISTANCEFACTOR 4.0f
namespace rah 
{
	enum ChannelsTypesNames
	{
		MASTER,
		MUSIC,
		FX,
		DEFAULT
	};

	class AudioManager : public rah::Module<AudioManager, void*>
	{
	private:
		FMOD::System* m_System;

		std::unordered_map<std::string, rahChannelGroup> m_ChannelGroups;
	public:
		RahResult Initialize(void* initValue = NULL);
		void Set3DSettings(float _DopplerScale = 1.0f, float _RollOffScale = 1.0f);
		void Release();
		FMOD::System* getSystem();
		bool findChannel(std::string _channelName);
		void PlayAudio(rahAudioFile* _Audio);
		std::string ChannelName(ChannelsTypesNames _name);

		void SetVolumeToAllChannels(float _volume);						
		void MuteAllChannels(bool _mute);
		void SetPausedToAllChannels(bool _paused);
		void StopAllChannels();

		void SetChannelGroupVolume(std::string _groupName, float _volume);
		void MuteChannelGroup(std::string _groupName, bool _mute);
		void SetChannelGroupPaused(std::string _groupName, bool _paused);
		void StopChannelGroup(std::string _groupName);
		AudioManager();
		~AudioManager();
	};
}

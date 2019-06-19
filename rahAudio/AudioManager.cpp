#include "AudioManager.h"


namespace rah
{
	RahResult AudioManager::Initialize(void * /*initValue*/)
	{
		FMOD_RESULT result;

		result = FMOD::System_Create(&m_System);

		result = m_System->init(MAX_CHANNELS, FMOD_INIT_NORMAL, NULL);

		Set3DSettings(1.0f, 1.0f);

		FMOD::ChannelGroup* master, *fx, *music, *default;

		result = m_System->createChannelGroup("FX", &fx);
		result = m_System->createChannelGroup("MUSIC", &music);
		result = m_System->createChannelGroup("DEFAULT", &default);
		result = m_System->getMasterChannelGroup(&master);

		master->addGroup(fx);
		master->addGroup(music);
		master->addGroup(default);

		m_ChannelGroups["MASTER"].m_ChannelGroup = master;
		m_ChannelGroups["MASTER"].m_Name = "MASTER";

		m_ChannelGroups["MUSIC"].m_ChannelGroup = music;
		m_ChannelGroups["MUSIC"].m_Name = "MUSIC";

		m_ChannelGroups["FX"].m_ChannelGroup = fx;
		m_ChannelGroups["FX"].m_Name = "FX";

		m_ChannelGroups["DEFAULT"].m_ChannelGroup = default;
		m_ChannelGroups["DEFAULT"].m_Name = "DEFAULT";

		return RAH_SUCCESS;
	}
	void AudioManager::Set3DSettings(float _DopplerScale, float _RollOffScale)
	{
		m_System->set3DSettings(_DopplerScale, DISTANCEFACTOR, _RollOffScale);
	}
	FMOD::System * AudioManager::getSystem()
	{
		return m_System;
	}
	bool AudioManager::findChannel(std::string _channelName)
	{
		if (m_ChannelGroups.find(_channelName) != m_ChannelGroups.end())
		{
			return true;
		}
		return false;
	}
	void AudioManager::PlayAudio(rahAudioFile * _Audio)
	{
		//if (!m_Listeners.empty())
		//{
			m_System->playSound(_Audio->m_sound, 0, true, &_Audio->m_channel->m_channel);
			_Audio->m_channel->m_channel->setChannelGroup(m_ChannelGroups[_Audio->m_channelGroup].m_ChannelGroup);
		//}
	}
	std::string AudioManager::ChannelName(ChannelsTypesNames _name)
	{
		if (_name == ChannelsTypesNames::MASTER)
			return "MASTER";
		else if (_name == ChannelsTypesNames::MUSIC)
			return "MUSIC";
		else if (_name == ChannelsTypesNames::FX)
			return "FX";
		else
			return "DEFAULT";
	}
	void AudioManager::SetVolumeToAllChannels(float _volume)
	{
		m_ChannelGroups["MASTER"].SetVolume(_volume);
	}
	void AudioManager::MuteAllChannels(bool _mute)
	{
		m_ChannelGroups["MASTER"].Mute(_mute);
	}
	void AudioManager::SetPausedToAllChannels(bool _paused)
	{
		m_ChannelGroups["MASTER"].SetPaused(_paused);
	}
	void AudioManager::StopAllChannels()
	{
		m_ChannelGroups["MASTER"].Stop();
	}
	void AudioManager::SetChannelGroupVolume(std::string _groupName, float _volume)
	{
		if (m_ChannelGroups.find(_groupName) != m_ChannelGroups.end())
		{
			m_ChannelGroups[_groupName].SetVolume(_volume);
		}
	}
	void AudioManager::MuteChannelGroup(std::string _groupName, bool _mute)
	{
		if (m_ChannelGroups.find(_groupName) != m_ChannelGroups.end())
		{
			m_ChannelGroups[_groupName].Mute(_mute);
		}
	}
	void AudioManager::SetChannelGroupPaused(std::string _groupName, bool _paused)
	{
		if (m_ChannelGroups.find(_groupName) != m_ChannelGroups.end())
		{
			m_ChannelGroups[_groupName].SetPaused(_paused);
		}
	}
	void AudioManager::StopChannelGroup(std::string _groupName)
	{
		if (m_ChannelGroups.find(_groupName) != m_ChannelGroups.end())
		{
			m_ChannelGroups[_groupName].Stop();
		}
	}
	void AudioManager::Update(float /*_deltatime*/)
	{
		m_System->update();
	}
	void AudioManager::Release()
	{
	}
	AudioManager::AudioManager()
	{
	}


	AudioManager::~AudioManager()
	{
	}
}
#include "rahAudioFile.h"
#include "AudioManager.h"
#include "AudioManager.h"

namespace rah
{
	rahAudioFile::rahAudioFile()
	{
	}


	rahAudioFile::~rahAudioFile()
	{
	}
	RahResult rahAudioFile::Initialize(BasicResourceParams * _params)
	{
		RahResult rtnValue;

		if (__super::Initialize(_params) != RahResult::RAH_SUCCESS)
			return RahResult::RAH_ERROR;

		AudioParams *tmp = (AudioParams*)_params;
		
		if(tmp->ChannelGroup.empty())
			return RahResult::RAH_ERROR;

		if (AudioManager::GetInstance().findChannel(tmp->ChannelGroup))
			m_channelGroup = tmp->ChannelGroup;
		else
			m_channelGroup = "DEFAULT";

		m_isStream = tmp->IsStream;
		m_mode = tmp->Mode;

		return RahResult::RAH_SUCCESS;
	}
	RahResult rahAudioFile::Load()
	{
		FMOD::System* sym = AudioManager::GetInstance().getSystem();

		if(sym == NULL)
			return RahResult::RAH_ERROR;

		FMOD_RESULT result;

		if (!m_isStream)
		{
			result = sym->createSound(m_filePath.Get().c_str(), m_mode, 0, &m_sound);
		}
		else
		{
			result = sym->createStream(m_filePath.Get().c_str(), m_mode, 0, &m_sound);
		}

		if (result != FMOD_OK)
			return RahResult::RAH_ERROR;

		Set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR);

		m_channel = new rah::rahChannel();
		result = sym->playSound(m_sound, 0, true, &m_channel->m_channel);

		if (result != FMOD_OK)
			return RahResult::RAH_ERROR;

		return RahResult::RAH_SUCCESS;
	}
	void rahAudioFile::Set3DMinMaxDistance(float min, float max)
	{
		m_sound->set3DMinMaxDistance(min, max);
	}
	void rahAudioFile::Play()
	{
		AudioManager::GetInstance().PlayAudio(this);
		m_channel->m_channel->setPaused(false);
	}
	void rahAudioFile::SetPaused(bool _paused)
	{
		m_isPaused = _paused;
		m_channel->m_channel->setPaused(m_isPaused);
	}
	void rahAudioFile::Stop()
	{
		m_channel->m_channel->stop();
	}
	void rahAudioFile::SetVolume(float _volume)
	{
		m_channel->m_channel->setVolume(_volume);
	}
	void rahAudioFile::Mute(bool _mute)
	{
		m_channel->m_channel->setMute(_mute);
	}
}
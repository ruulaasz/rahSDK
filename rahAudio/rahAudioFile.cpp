#include "rahAudioFile.h"
#include "AudioManager.h"
#include "AudioManager.h"

namespace rah
{
	rahAudioFile::rahAudioFile()
	{
		m_volume = 3;
	}

	rahAudioFile::~rahAudioFile()
	{

	}

	RahResult rahAudioFile::Initialize(BasicResourceParams * _params)
	{
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

	void rahAudioFile::Release()
	{
		m_sound->release();
		m_channel->m_channel->stop();
		RAH_SAFE_DELETE(m_channel);
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

	void rahAudioFile::UpdatePositionVelocity(Vector3D _position, Vector3D _velocity)
	{
		m_position = _position;
		m_velocity = _velocity;

		FMOD_VECTOR pos, vel;
		pos.x = m_position.x;
		pos.y = m_position.y;
		pos.z = m_position.z;

		vel.x = m_velocity.x;
		vel.y = m_velocity.y;
		vel.z = m_velocity.z;
		m_channel->m_channel->set3DAttributes(&pos, &vel);
	}
}
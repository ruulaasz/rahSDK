#include "AudioComponent.h"

namespace rah
{
	AudioComponent::AudioComponent()
	{
	}


	AudioComponent::~AudioComponent()
	{
	}
	void AudioComponent::init(Actor * _owner, void * _data)
	{
		AudioParams* data = reinterpret_cast<AudioParams*>(_data);

		if (data != NULL)
		{
			m_audio = (rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(data, rah::ResourceTypes::RAH_Audio);
		}
		else
		{
			rah::AudioParams aprm;
			aprm.ChannelGroup = rah::AudioManager::GetInstance().ChannelName(rah::ChannelsTypesNames::DEFAULT);
			aprm.filePath = "resources\\audio\\Gorillaz - Clint Eastwood (Official Video) (128  kbps).mp3";
			aprm.IsStream = false;
			aprm.Mode = rah::rahSoundMode::MODE_3D;
			m_audio = (rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&aprm, rah::ResourceTypes::RAH_Audio);
		}

		m_owner = _owner;
		m_lastOwnerPosition = m_owner->m_transform.m_position;
	}
	void AudioComponent::render()
	{
		if (m_rendereable)
		{
			RenderManager::GetInstance().renderShape(AABB(m_owner->m_transform.m_position, Vector4D(-1.f, -1.f, -1.f), Vector4D(1.f, 1.f, 1.f)), Color::green);
		}
	}
	void AudioComponent::update(float _deltaTime)
	{
		if (m_audio != NULL)
		{
			Vector3D velocity;
			velocity.x = (m_owner->m_transform.m_position.x - m_lastOwnerPosition.x) / _deltaTime;
			velocity.y = (m_owner->m_transform.m_position.y - m_lastOwnerPosition.y) / _deltaTime;
			velocity.z = (m_owner->m_transform.m_position.z - m_lastOwnerPosition.z) / _deltaTime;

			m_audio->UpdatePositionVelocity(m_owner->m_transform.m_position, velocity);

			m_lastOwnerPosition = m_owner->m_transform.m_position;
		}
	}
	void AudioComponent::Play()
	{
		if (m_audio != NULL)
		{
			m_audio->Play();
		}
	}
	void AudioComponent::SetVolume(float _volume)
	{
		if (m_audio != NULL)
		{
			m_audio->SetVolume(_volume);
		}
	}
}
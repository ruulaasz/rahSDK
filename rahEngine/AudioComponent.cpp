#include "AudioComponent.h"
#include "rahAll.h"
#include "rahEngine.h"

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
		AudioComponentParams* data = reinterpret_cast<AudioComponentParams*>(_data);

		if (data != NULL)
		{
			size_t size = sizeof(data) / sizeof(AudioParams);
			m_audioNumber = size;

			for (size_t i = 0; i < m_audioNumber; i++)
			{
				m_audio.push_back((rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(data[i].params, rah::ResourceTypes::RAH_Audio));
			}		
		}
		else
		{
			rah::AudioParams parms;
			parms.ChannelGroup = rah::AudioManager::GetInstance().ChannelName(rah::ChannelsTypesNames::DEFAULT);
			parms.filePath = "resources\\audio\\Gorillaz - Clint Eastwood (Official Video) (128  kbps).mp3";
			parms.IsStream = false;
			parms.Mode = rah::rahSoundMode::MODE_3D;

			m_audio.push_back((rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&parms, rah::ResourceTypes::RAH_Audio));
			m_audioNumber = 1;
		}

		m_owner = _owner;
		m_lastOwnerPosition = m_owner->m_transform.m_position;
	}

	void AudioComponent::render()
	{
		ImgManager::GetInstance().audioComponentGUI(this);

		if (m_rendereable)
		{
			RenderManager::GetInstance().renderShape(AABB(m_owner->m_transform.m_position, Vector4D(-1.f, -1.f, -1.f), Vector4D(1.f, 1.f, 1.f)), Color::green);
		}
	}

	void AudioComponent::update(float _deltaTime)
	{
		for (size_t i = 0; i < m_audioNumber; i++)
		{
			if (m_audio.at(i) != NULL)
			{
				Vector3D velocity;
				velocity.x = (m_owner->m_transform.m_position.x - m_lastOwnerPosition.x) / _deltaTime;
				velocity.y = (m_owner->m_transform.m_position.y - m_lastOwnerPosition.y) / _deltaTime;
				velocity.z = (m_owner->m_transform.m_position.z - m_lastOwnerPosition.z) / _deltaTime;

				m_audio.at(i)->UpdatePositionVelocity(m_owner->m_transform.m_position, velocity);

				m_lastOwnerPosition = m_owner->m_transform.m_position;
			}
		}
	}

	void AudioComponent::addAudioFile(AudioParams params)
	{
		m_audio.push_back((rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&params, rah::ResourceTypes::RAH_Audio));
		++m_audioNumber;
	}
}
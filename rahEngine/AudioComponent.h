#pragma once
#include "Component.h"
#include "rahAll.h"
#include "Actor.h"

namespace rah
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent();
		~AudioComponent();

		virtual void init(Actor* _owner, void* _data = NULL);
		virtual void render();
		virtual void update(float _deltaTime);
		void Play();
		void SetVolume(float _volume);
		rahAudioFile* m_audio;
		Vector3D m_lastOwnerPosition;
	};
}

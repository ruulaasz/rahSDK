#pragma once

#include "Component.h"
#include "rahAll.h"
#include "Actor.h"

namespace rah
{
	struct AudioComponentParams
	{
		AudioParams* params;
	};

	class AudioComponent : public Component
	{
	public:
		AudioComponent();
		~AudioComponent();

		virtual void init(Actor* _owner, void* _data = NULL);
		virtual void render();
		virtual void update(float _deltaTime);

		void addAudioFile(AudioParams params);

		std::vector<rahAudioFile*> m_audio;
		Vector3D m_lastOwnerPosition;
		bool m_mute;
		size_t m_audioNumber;
	};
}
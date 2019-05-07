#pragma once
#include <fmod.hpp>
#include <rahTools.h>
#include <rahMath.h>
#include "rahChannel.h"

namespace rah
{
	enum rahSoundMode
	{
		MODE_3D = FMOD_3D,
		MODE_2D = FMOD_2D,
		MODE_LOOP_ON = FMOD_LOOP_NORMAL,
		MODE_LOOP_OFF = FMOD_LOOP_OFF
	};
	struct AudioParams : public BasicResourceParams
	{
		rahSoundMode Mode = MODE_3D;
		std::string ChannelGroup = "DEFAULT";
		bool IsStream = false;
	};
	class rahAudioFile : public rahResource
	{
	public:
		rahAudioFile();
		~rahAudioFile();

		Vector3D m_position;
		Vector3D m_velocity;
		std::string m_channelGroup;
		rah::rahChannel* m_channel;
		FMOD::Sound* m_sound;
		rahSoundMode m_mode;
		bool m_isStream;
		bool m_isPaused;

		virtual RahResult Initialize(BasicResourceParams* _params);
		RahResult Load();
		void Release() {};
		void Set3DMinMaxDistance(float min, float max);
		void Play();
		void SetPaused(bool _paused);							
		void Stop();
		void SetVolume(float _volume);
		void Mute(bool _mute);											
	};
}

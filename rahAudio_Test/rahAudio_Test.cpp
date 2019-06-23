// rahAudio_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <rahEngine.h>
#include <iostream>

int main()
{
	rah::AudioManager::StartModule(NULL);
	RAH_DEBUGER_MODULE_DECLARATION();
	RahResult msg = rah::AudioManager::GetLastError();
	if (msg != RahResult::RAH_SUCCESS)
		RAH_LOG("fail thiz shit");

	rah::ResourceManagerInit managerInit;
	rah::ResourceFabric* resourcefabric = new rah::ResourceFabric();
	managerInit.Fabric = resourcefabric;
	rah::ResourceManager::StartModule(managerInit);
	msg = rah::ResourceManager::GetLastError();
	if (msg != RahResult::RAH_SUCCESS)
		RAH_LOG("fail thiz shit");

	rah::rahAudioFile* audio;
	rah::AudioParams aprm;
	aprm.ChannelGroup = rah::AudioManager::GetInstance().ChannelName(rah::ChannelsTypesNames::MUSIC);
	aprm.filePath = "Audio\\Cartoons - Witch Doctor (128  kbps).mp3";
	aprm.IsStream = false;
	aprm.Mode = rah::rahSoundMode::MODE_3D;
	audio = (rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&aprm, rah::ResourceTypes::RAH_Audio);
	//audio->UpdatePositionVelocity(rah::Vector3D(100.0f, 100.0f), rah::Vector3D(0.0f));
	audio->m_channel->m_channel->set3DLevel(0.2);
	audio->Set3DMinMaxDistance(0.0f, 10.0f);
	rah::rahListener listener;

	listener.m_up = rah::Vector3D(0.0f, 1.0f);
	listener.m_forward = rah::Vector3D(0.0f, 0.0f, 1.0f);

	rah::rahAudioFile* audio2;
	rah::AudioParams aprm2;
	aprm2.ChannelGroup = rah::AudioManager::GetInstance().ChannelName(rah::ChannelsTypesNames::FX);
	aprm2.filePath = "Audio\\Gorillaz - Clint Eastwood (Official Video) (128  kbps).mp3";
	aprm2.IsStream = false;
	aprm2.Mode = rah::rahSoundMode::MODE_2D;
	audio2 = (rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&aprm2, rah::ResourceTypes::RAH_Audio);

	if (msg != RahResult::RAH_SUCCESS)
		RAH_LOG("fail thiz shit");

	audio->Play();
	//audio2->Play();
	bool mute = true;
	int voulmen = 5;
	audio->SetVolume(voulmen);
	std::cout << "m: Mute" << std::endl;
	std::cout << "p: Pause" << std::endl;
	std::cout << "s: Stop" << std::endl;
	std::cout << "q: play" << std::endl;
	std::cout << "z: Volumen up" << std::endl;
	std::cout << "x: Volumen down" << std::endl;

	while (true)
	{
		audio->UpdatePositionVelocity(rah::Vector3D(10.0f, 10.0f), rah::Vector3D(0.0f));
		char x = 0;
		std::cin >> x;
		/*if (x == 'm')
		{
			mute = !mute;
			audio->Mute(mute);
		}
		else if (x == 'p')
		{
			audio->SetPaused(!audio->m_isPaused);
		}
		else if (x == 's')
		{
			audio->Stop();
		}
		else if (x == 'q')
		{
			audio->Play();
		}
		else if (x == 'z')
		{
			voulmen++;
			if (voulmen >= 10)
			{
				voulmen = 10;
			}
			audio->SetVolume(voulmen);
		}
		else if (x == 'x')
		{
			voulmen--;
			if (voulmen <= 0)
			{
				voulmen = 0;
			}
			audio->SetVolume(voulmen);
		}*/
		if (x == 'a')
		{
			listener.m_position.x -= DISTANCEFACTOR;
			listener.UpdateListener(listener.m_position, listener.m_velocity, listener.m_forward, listener.m_up);
		}
		else if (x == 'w')
		{
			listener.m_position.y += DISTANCEFACTOR;
			listener.UpdateListener(listener.m_position, listener.m_velocity, listener.m_forward, listener.m_up);
		}
		else if (x == 's')
		{
			listener.m_position.y -= DISTANCEFACTOR;
			listener.UpdateListener(listener.m_position, listener.m_velocity, listener.m_forward, listener.m_up);
		}
		else if (x == 'd')
		{
			listener.m_position.x += DISTANCEFACTOR;
			listener.UpdateListener(listener.m_position, listener.m_velocity, listener.m_forward, listener.m_up);
		}
		std::cin.clear();
		rah::AudioManager::GetInstance().Update();
	}

    return 0;
}


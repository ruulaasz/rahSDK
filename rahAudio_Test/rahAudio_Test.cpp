// rahAudio_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <rahEngine.h>

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
	aprm.ChannelGroup = "DEFAULT";
	aprm.filePath = "Audio\\Cartoons - Witch Doctor (128  kbps).mp3";
	aprm.IsStream = false;
	aprm.Mode = rah::rahSoundMode::MODE_2D;
	audio = (rah::rahAudioFile*)rah::ResourceManager::GetInstance().LoadResource(&aprm, rah::ResourceTypes::RAH_Audio);

	if (msg != RahResult::RAH_SUCCESS)
		RAH_LOG("fail thiz shit");

	audio->Play();

	while (true)
	{

	}

    return 0;
}


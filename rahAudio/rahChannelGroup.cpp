#include "rahChannelGroup.h"


namespace rah
{
	rahChannelGroup::rahChannelGroup()
	{
	}


	rahChannelGroup::~rahChannelGroup()
	{
	}

	void rahChannelGroup::SetVolume(float _Volume)
	{
		m_ChannelGroup->setVolume(_Volume);
	}

	void rahChannelGroup::SetPaused(bool _paused)
	{
		m_ChannelGroup->setPaused(_paused);
	}

	void rahChannelGroup::Stop()
	{
		m_ChannelGroup->stop();
	}

	void rahChannelGroup::SetPitch(float _Pitch)
	{
		m_ChannelGroup->setPitch(_Pitch);
	}

	void rahChannelGroup::Mute()
	{
		m_ChannelGroup->setMute(true);
	}

	void rahChannelGroup::UnMute()
	{
		m_ChannelGroup->setMute(false);
	}

	void rahChannelGroup::AddGroup(rahChannelGroup * _Group)
	{
		m_ChannelGroup->addGroup(_Group->m_ChannelGroup);
	}
}
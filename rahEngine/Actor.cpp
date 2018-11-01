#include "Actor.h"


namespace rah
{
	int rah::Actor::m_autoID = 0;
	Actor::Actor()
	{
		m_id = m_autoID;
		m_autoID++;
	}


	Actor::~Actor()
	{
	}
}
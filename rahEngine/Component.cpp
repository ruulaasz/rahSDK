#include "Component.h"
#include "Actor.h"

namespace rah
{
	Component::Component()
	{
		m_enabled = true;
		m_rendereable = true;
	}

	Component::~Component()
	{

	}
}
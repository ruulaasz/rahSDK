#pragma once
#include <rahTools.h>
#include <rahMath.h>

namespace rah
{
	class rahListener
	{
	public:
		static int m_autoID;
		int m_id;
		Vector3D m_position;
		Vector3D m_velocity;
		Vector3D m_forward;
		Vector3D m_up;
		
		rahListener();
		~rahListener();

		void UpdateListener(Vector3D _pos, Vector3D _vel, Vector3D _forward, Vector3D _up);
	};
}

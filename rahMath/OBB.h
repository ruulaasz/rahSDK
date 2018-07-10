#pragma once
#include "Vector3D.h"

namespace rah
{
	/**
	* A Oriented Bounding Box
	*
	*/
	class OBB
	{
	public:
		OBB();
		OBB(Vector3D _pos, Vector3D _dimentions, Vector3D _axisX, Vector3D _axisY, Vector3D _axisZ);
		OBB(const OBB &_obb);
		~OBB();

		Vector3D m_position;
		Vector3D m_dimentions;
		Vector3D m_axis[3];
	};
}
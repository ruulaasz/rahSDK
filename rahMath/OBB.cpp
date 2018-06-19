#include "OBB.h"

namespace rah
{
	OBB::OBB()
	{

	}

	OBB::OBB(Vector3D _pos, Vector3D _dimentions, Vector3D _axisX, Vector3D _axisY, Vector3D _axisZ)
	{
		m_position = _pos;
		m_dimentions = _dimentions;
		m_axis[0] = _axisX;
		m_axis[1] = _axisY;
		m_axis[2] = _axisZ;
	}

	OBB::OBB(const OBB & _obb)
	{
		m_position = _obb.m_position;
		m_dimentions = _obb.m_dimentions;
		m_axis[0] = _obb.m_axis[0];
		m_axis[1] = _obb.m_axis[1];
		m_axis[2] = _obb.m_axis[2];
	}

	OBB::~OBB()
	{

	}
}
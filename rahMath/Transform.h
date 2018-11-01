#pragma once
#include "Vector3D.h"
#include "Matrix4D.h"

namespace rah
{
	class Transform
	{
	public:
		Vector3D m_position;
		Vector3D m_rotation;
		Vector3D m_scale;
	public:
		Matrix4D TransformToWorldMatrix();
		Transform(Vector3D _pos = Vector3D(0), Vector3D _rot = Vector3D(0), Vector3D _scale = Vector3D(0));
		Transform(float _all);
		~Transform();
	};
}

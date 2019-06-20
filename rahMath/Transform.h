#pragma once

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"

namespace rah
{
	class Transform
	{
	public:
		Matrix4D TransformToWorldMatrix();
		bool operator==(Transform _other);
		bool operator!=(Transform _other);
		explicit Transform(Vector3D _pos = Vector3D(0), Vector3D _rot = Vector3D(0), Vector3D _scale = Vector3D(0));

		Transform(Vector4D _pos, Vector4D _rot = Vector4D(0), Vector4D _scale = Vector4D(0));
		Transform(float _all);
		~Transform();

		Vector3D m_position;
		Vector3D m_rotation;
		Vector3D m_scale;
	};
}

#include "Transform.h"
#include "PlatformMath.h"
#include "Degrees.h"

namespace rah
{
	Matrix4D Transform::TransformToWorldMatrix()
	{
		Matrix4D trans, rot, sca, world;

		trans = rah::math::TranslationMatrix4x4(m_position);

		sca = rah::math::ScalarMatrix4x4(m_scale);

		rot = rah::math::RotationMatrix4x4(rah::Degrees(m_rotation.x).getRadians(), rah::math::Axis_X);
		rot = rot * rah::math::RotationMatrix4x4(rah::Degrees(m_rotation.y).getRadians(), rah::math::Axis_Y);
		rot = rot * rah::math::RotationMatrix4x4(rah::Degrees(m_rotation.z).getRadians(), rah::math::Axis_Z);

		world = rah::math::Identity4D();

		world = sca * rot * trans;

		return world;
	}

	Transform::Transform(Vector3D _pos, Vector3D _rot, Vector3D _scale)
	{
		m_position = _pos;
		m_rotation = _rot;
		m_scale = _scale;
	}

	Transform::Transform(Vector4D _pos, Vector4D _rot, Vector4D _scale)
	{
		m_position.x = _pos.x;
		m_position.y = _pos.y;
		m_position.z = _pos.z;

		m_rotation.x = _rot.x;
		m_rotation.y = _rot.y;
		m_rotation.z = _rot.z;

		m_scale.x = _scale.x;
		m_scale.y = _scale.y;
		m_scale.z = _scale.z;
	}

	Transform::Transform(float _all)
	{
		m_position = Vector3D(_all);
		m_rotation = Vector3D(_all);
		m_scale = Vector3D(_all);
	}


	Transform::~Transform()
	{
	}
}
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
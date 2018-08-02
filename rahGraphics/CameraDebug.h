#pragma once
#include "Camera.h"
#include <Vector3D.h>
#include <Frustum.h>

namespace rah
{
	class CameraDebug : public Camera
	{
	public:
		CameraDebug();
		~CameraDebug();

		// The camera's position
		Vector3D m_vPosition;

		// The camera's view
		Vector3D m_vView;

		// The camera's up vector
		Vector3D m_vUpVector;

		// The camera's strafe vector
		Vector3D m_vStrafe;

		Frustum m_frustum;

		// This changes the position, view, and up vector of the camera.
		// This is primarily used for initialization
		void PositionCamera(Vector3D _eye, Vector3D _at, Vector3D _up);

		// This rotates the camera's view around the position depending on the values passed in.
		void RotateView(float angle, float X, float Y, float Z);

		// This moves the camera's view by the mouse movements (First person view)
		void SetViewByMouse();

		// This strafes the camera left or right depending on the speed (+/-) 
		void StrafeCamera(float speed);

		// This will move the camera forward or backward depending on the speed
		void MoveCamera(float speed);

		// This updates the camera's view and other data (Should be called each frame)
		void Update();
	};
}
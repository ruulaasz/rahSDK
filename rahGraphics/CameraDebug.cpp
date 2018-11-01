#include "CameraDebug.h"
#include <PlatformMath.h>
#include "GraphicManager.h"
#include <Windows.h>
#include "RenderManager.h"

namespace rah
{
	CameraDebug::CameraDebug()
	{
		m_stopMoving = false;
	}

	CameraDebug::~CameraDebug()
	{

	}

	void CameraDebug::PositionCamera(Vector3D _eye, Vector3D _at, Vector3D _up)
	{
		// The code above just makes it cleaner to set the variables.
		// Otherwise we would have to set each variable x y and z.

		m_vPosition = _eye;					// Assign the position
		m_vView = _at;						// Assign the view
		m_vUpVector = _up;					// Assign the up vector
	}

	void CameraDebug::RotateView(float angle, float x, float y, float z)
	{
		Vector3D vNewView;

		// Get the view vector (The direction we are facing)
		Vector3D vView = m_vView - m_vPosition;

		// Calculate the sine and cosine of the angle once
		float cosTheta = (float)cos(angle);
		float sinTheta = (float)sin(angle);

		// Find the new x position for the new rotated point
		vNewView.x = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
		vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
		vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

		// Find the new y position for the new rotated point
		vNewView.y = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
		vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
		vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

		// Find the new z position for the new rotated point
		vNewView.z = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
		vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
		vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

		// Now we just add the newly rotated vector to our position to set
		// our new rotated view of our camera.
		m_vView = m_vPosition + vNewView;
	}

	void CameraDebug::SetViewByMouse()
	{
		POINT mousePos;									// This is a window structure that holds an X and Y
		int middleX = rah::GraphicManager::GetInstance().m_width >> 1;				// This is a binary shift to get half the width
		int middleY = rah::GraphicManager::GetInstance().m_width >> 1;				// This is a binary shift to get half the height
		float angleY = 0.0f;							// This is the direction for looking up or down
		float angleZ = 0.0f;							// This will be the value we need to rotate around the Y axis (Left and Right)
		static float currentRotX = 0.0f;

		// Get the mouse's current X,Y position
		GetCursorPos(&mousePos);

		// If our cursor is still in the middle, we never moved... so don't update the screen
		if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

		// Set the mouse position to the middle of our window
		SetCursorPos(middleX, middleY);

		// Get the direction the mouse moved in, but bring the number down to a reasonable amount
		angleY = (float)((middleX - mousePos.x)) / 500.0f;
		angleZ = (float)((middleY - mousePos.y)) / 500.0f;

		static float lastRotX = 0.0f;
		lastRotX = currentRotX; // We store off the currentRotX and will use it in when the angle is capped

								// Here we keep track of the current rotation (for up and down) so that
								// we can restrict the camera from doing a full 360 loop.
		currentRotX += angleZ;

		// If the current rotation (in radians) is greater than 1.0, we want to cap it.
		if (currentRotX > 1.0f)
		{
			currentRotX = 1.0f;

			// Rotate by remaining angle if there is any
			if (lastRotX != 1.0f)
			{
				// To find the axis we need to rotate around for up and down
				// movements, we need to get a perpendicular vector from the
				// camera's view vector and up vector.  This will be the axis.
				// Before using the axis, it's a good idea to normalize it first.
				Vector3D vAxis = math::CrossProduct(m_vView - m_vPosition, m_vUpVector);
				math::Normalize(vAxis);

				// rotate the camera by the remaining angle (1.0f - lastRotX)
				RotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
			}
		}
		// Check if the rotation is below -1.0, if so we want to make sure it doesn't continue
		else if (currentRotX < -1.0f)
		{
			currentRotX = -1.0f;

			// Rotate by the remaining angle if there is any
			if (lastRotX != -1.0f)
			{
				// To find the axis we need to rotate around for up and down
				// movements, we need to get a perpendicular vector from the
				// camera's view vector and up vector.  This will be the axis.
				// Before using the axis, it's a good idea to normalize it first.
				Vector3D vAxis = math::CrossProduct(m_vView - m_vPosition, m_vUpVector);
				math::Normalize(vAxis);

				// rotate the camera by ( -1.0f - lastRotX)
				RotateView(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
			}
		}
		// Otherwise, we can rotate the view around our position
		else
		{
			// To find the axis we need to rotate around for up and down
			// movements, we need to get a perpendicular vector from the
			// camera's view vector and up vector.  This will be the axis.
			// Before using the axis, it's a good idea to normalize it first.
			Vector3D vAxis = math::CrossProduct(m_vView - m_vPosition, m_vUpVector);
			math::Normalize(vAxis);

			// Rotate around our perpendicular axis
			RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
		}

		// Always rotate the camera around the y-axis
		RotateView(angleY*(-1), 0, 1, 0);
	}

	void CameraDebug::StrafeCamera(float speed)
	{
		// Add the strafe vector to our position
		m_vPosition.x += m_vStrafe.x * speed;
		m_vPosition.z += m_vStrafe.z * speed;

		// Add the strafe vector to our view
		m_vView.x += m_vStrafe.x * speed;
		m_vView.z += m_vStrafe.z * speed;
	}

	void CameraDebug::MoveCamera(float speed)
	{
		// Get the current view vector (the direction we are looking)
		Vector3D vVector = m_vView - m_vPosition;
		math::Normalize(vVector);

		m_vPosition.x += vVector.x * speed;		// Add our acceleration to our position's X
		m_vPosition.y += vVector.y * speed;		// Add our acceleration to our position's Y
		m_vPosition.z += vVector.z * speed;		// Add our acceleration to our position's Z
		m_vView.x += vVector.x * speed;			// Add our acceleration to our view's X
		m_vView.y += vVector.y * speed;			// Add our acceleration to our view's Y
		m_vView.z += vVector.z * speed;			// Add our acceleration to our view's Z
	}

	void CameraDebug::Update()
	{
		// Initialize a variable for the cross product result
		Vector3D vCross = math::CrossProduct(m_vView - m_vPosition, m_vUpVector);
	
		// Normalize the strafe vector
		math::Normalize(vCross);
		m_vStrafe = vCross;

		// Move the camera's view by the mouse
		if(!m_stopMoving)
			SetViewByMouse();

		RenderManager::GetInstance().updateView(math::LookAtLH(m_vPosition, m_vView, m_vUpVector));
		m_frustum.calculateFrustum(RenderManager::GetInstance().m_projection, RenderManager::GetInstance().m_view);
	}
}
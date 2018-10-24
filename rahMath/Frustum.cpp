#include "Frustum.h"
#include "PlatformMath.h"
#include "Intersection.h"

namespace rah
{
	Frustum::Frustum()
	{

	}

	Frustum::Frustum(const Frustum & _frustum)
	{
		m_planes[0] = _frustum.m_planes[0];
		m_planes[1] = _frustum.m_planes[1];
		m_planes[2] = _frustum.m_planes[2];
		m_planes[3] = _frustum.m_planes[3];
		m_planes[4] = _frustum.m_planes[4];
		m_planes[5] = _frustum.m_planes[5];
	}

	Frustum::~Frustum()
	{

	}

	void Frustum::normalizePlane(FrustumSide _side)
	{
		// Here we calculate the magnitude of the normal to the plane (point A B C)
		// Remember that (A, B, C) is that same thing as the normal's (X, Y, Z).
		// To calculate magnitude you use the equation:  magnitude = sqrt( x^2 + y^2 + z^2)
		float magnitude = (float)sqrt(m_planes[_side].a * m_planes[_side].a +
			m_planes[_side].b * m_planes[_side].b +
			m_planes[_side].c * m_planes[_side].c);

		// Then we divide the plane's values by it's magnitude.
		// This makes it easier to work with.
		m_planes[_side].a /= magnitude;
		m_planes[_side].b /= magnitude;
		m_planes[_side].c /= magnitude;
		m_planes[_side].d /= magnitude;
	}

	void Frustum::calculateFrustum(Matrix4D _proj, Matrix4D _view)
	{
		Matrix4D clip;								// This will hold the clipping planes

		// Now that we have our modelview and projection matrix, if we combine these 2 matrices,
		// it will give us our clipping planes.  To combine 2 matrices, we multiply them.

		clip = _proj * _view;

		// Now we actually want to get the sides of the frustum.  To do this we take
		// the clipping planes we received above and extract the sides from them.

		// This will extract the RIGHT side of the frustum
		m_planes[RIGHT].a = clip.m03 - clip.m00;
		m_planes[RIGHT].b = clip.m13 - clip.m10;
		m_planes[RIGHT].c = clip.m23 - clip.m20;
		m_planes[RIGHT].d = clip.m33 - clip.m30;

		// Now that we have a normal (A,B,C) and a distance (D) to the plane,
		// we want to normalize that normal and distance.

		// Normalize the RIGHT side
		normalizePlane(RIGHT);

		// This will extract the LEFT side of the frustum
		m_planes[LEFT].a = clip.m03 + clip.m00;
		m_planes[LEFT].b = clip.m13 + clip.m10;
		m_planes[LEFT].c = clip.m23 + clip.m20;
		m_planes[LEFT].d = clip.m33 + clip.m30;

		// Normalize the LEFT side
		normalizePlane(LEFT);

		// This will extract the BOTTOM side of the frustum
		m_planes[BOTTOM].a = clip.m03 + clip.m01;
		m_planes[BOTTOM].b = clip.m13 + clip.m11;
		m_planes[BOTTOM].c = clip.m23 + clip.m21;
		m_planes[BOTTOM].d = clip.m33 + clip.m31;

		// Normalize the BOTTOM side
		normalizePlane(BOTTOM);

		// This will extract the TOP side of the frustum
		m_planes[TOP].a = clip.m03 - clip.m01;
		m_planes[TOP].b = clip.m13 - clip.m11;
		m_planes[TOP].c = clip.m23 - clip.m21;
		m_planes[TOP].d = clip.m33 - clip.m31;

		// Normalize the TOP side
		normalizePlane(TOP);

		// This will extract the BACK side of the frustum
		m_planes[BACK].a = clip.m03 - clip.m02;
		m_planes[BACK].b = clip.m13 - clip.m12;
		m_planes[BACK].c = clip.m23 - clip.m22;
		m_planes[BACK].d = clip.m33 - clip.m32;

		// Normalize the BACK side
		normalizePlane(BACK);

		// This will extract the FRONT side of the frustum
		m_planes[FRONT].a = clip.m03 + clip.m02;
		m_planes[FRONT].b = clip.m13 + clip.m12;
		m_planes[FRONT].c = clip.m23 + clip.m22;
		m_planes[FRONT].d = clip.m33 + clip.m32;

		// Normalize the FRONT side
		normalizePlane(FRONT);
	}

	AABB Frustum::getBox()
	{
		Vector3D p;
		Intersection::CheckIntersection(m_planes[TOP], m_planes[LEFT], m_planes[FRONT], p);
		
		return AABB();
	}

	void Frustum::render()
	{

	}
}
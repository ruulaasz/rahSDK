#pragma once

#include "Matrix4D.h"
#include "Plane.h"
#include "AABB.h"

namespace rah
{
	enum FrustumSide
	{
		RIGHT = 0,		// The RIGHT side of the frustum
		LEFT = 1,		// The LEFT	 side of the frustum
		BOTTOM = 2,		// The BOTTOM side of the frustum
		TOP = 3,		// The TOP side of the frustum
		BACK = 4,		// The BACK	side of the frustum
		FRONT = 5,		// The FRONT side of the frustum
		NUMPLANES
	};

	/**
	* A Frustum container class
	*
	*/
	class Frustum
	{
	public:
		Frustum();
		Frustum(const Frustum &_frustum);
		~Frustum();

		Plane m_planes[NUMPLANES];

		void normalizePlane(FrustumSide _side);
		void calculateFrustum(Matrix4D _proj, Matrix4D _view);
		AABB getBox();

		void render();
	};
}
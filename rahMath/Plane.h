#pragma once
#include "Vector3D.h"

namespace rah
{
	/**
	* A Geometric Plane
	*
	*/
	class Plane
	{
	public:
		Plane();
		Plane(Vector3D _A, Vector3D _B, Vector3D _C);
		Plane(Vector3D _normal, float _origin);
		Plane(const Plane& _plane);
		~Plane();

		//normal
		float a;
		float b;
		float c;

		//distancia al origen
		float d;

		void render();
		void initFromVectors(Vector3D _A, Vector3D _B, Vector3D _C);
	};
}
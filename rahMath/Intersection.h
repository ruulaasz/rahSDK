#pragma once
#include "Sphere.h"
#include "OBB.h"
namespace rah
{
	/*
	* Class for all intersections betew geometries
	*
	*/
	class Intersection
	{
	public:
		/*
		* Sphere vs sphere
		*
		*/
		static bool SphereIntersection(Sphere a, Sphere b);
		/*
		* OBB vs OBB
		*
		*/
		static bool OBBIntersection(OBB a, OBB b);
	public:
		Intersection();
		~Intersection();
	};
}

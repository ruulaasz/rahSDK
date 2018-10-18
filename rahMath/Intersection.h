#pragma once
#include "Sphere.h"
#include "OBB.h"
#include "Ray.h"
#include "Plane.h"
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
		/*
		* OBB vs Sphere
		*
		*/
		static bool SphereNOBBIntersection(Sphere s, OBB b);
		static void ClosestPtPointOBB(Vector3D p, OBB b, Vector3D &q);
		static bool RayNPlaneIntersection(Ray _ray, Plane _plane);
	public:
		Intersection();
		~Intersection();
	};
}

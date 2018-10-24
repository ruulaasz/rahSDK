#pragma once
#include "Sphere.h"
#include "OBB.h"
#include "Ray.h"
#include "Plane.h"
#include "AABB.h"
#include "Frustum.h"
namespace rah
{
	/*
	* Class for all intersections betew geometries
	*
	*/
	class Intersection
	{
	public:
		static bool CheckIntersection(Sphere a, Sphere b);
		static bool CheckIntersection(OBB a, OBB b);
		static bool CheckIntersection(Sphere s, OBB b);
		static bool CheckIntersection(OBB b, Sphere s);
		static bool CheckIntersection(Ray r, Plane p);
		static bool CheckIntersection(Plane p, Ray r);
		static bool CheckIntersection(AABB a, AABB b);
		static bool CheckIntersection(AABB a, Sphere s);
		static bool CheckIntersection(Sphere s, AABB a);
		static bool CheckIntersection(Plane p1, Plane p2, Vector3D &p, Vector3D &d);
		static bool CheckIntersection(Plane p1, Plane p2, Plane p3, Vector3D &p);
		static bool CheckIntersection(Frustum f, Vector3D p);
		static bool CheckIntersection(Vector3D p, Frustum f);
		static bool CheckIntersection(Frustum f, Sphere s);
		static bool CheckIntersection(Sphere s, Frustum f);
		static bool CheckIntersection(Frustum f, AABB a);
		static bool CheckIntersection(AABB a, Frustum f);
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
		static bool AABBIntersection(AABB _a, AABB _b);
		static bool AABBNSphereIntersection(AABB _a, Sphere _s);
		static bool PlaneIntersection(Plane p1, Plane p2, Vector3D &p, Vector3D &d);
		static bool PlaneIntersection(Plane p1, Plane p2, Plane p3, Vector3D &p);
		static bool FrustrumNPointIntersection(Frustum f, Vector3D p);
		static bool FrustrumNSphereIntersection(Frustum f, Sphere s);
		static bool FrustumNAABBIntersection(Frustum f, AABB a);
	public:
		Intersection();
		~Intersection();
	};
}

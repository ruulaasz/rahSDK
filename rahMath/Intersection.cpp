#include "Intersection.h"
#include "Vector3D.h"
#include "PlatformMath.h"

namespace rah
{
	bool Intersection::CheckIntersection(Sphere a, Sphere b)
	{
		return SphereIntersection(a,b);
	}
	bool Intersection::CheckIntersection(OBB a, OBB b)
	{
		return OBBIntersection(a,b);
	}
	bool Intersection::CheckIntersection(Sphere s, OBB b)
	{
		return SphereNOBBIntersection(s,b);
	}
	bool Intersection::CheckIntersection(OBB b, Sphere s)
	{
		return SphereNOBBIntersection(s, b);
	}
	bool Intersection::CheckIntersection(Ray r, Plane p)
	{
		return RayNPlaneIntersection(r, p);
	}
	bool Intersection::CheckIntersection(Plane p, Ray r)
	{
		return RayNPlaneIntersection(r, p);
	}
	bool Intersection::CheckIntersection(AABB a, AABB b)
	{
		return AABBIntersection(a,b);
	}
	bool Intersection::CheckIntersection(AABB a, Sphere s)
	{
		return AABBNSphereIntersection(a,s);
	}
	bool Intersection::CheckIntersection(Sphere s, AABB a)
	{
		return AABBNSphereIntersection(a, s);
	}
	bool Intersection::CheckIntersection(Plane p1, Plane p2, Vector3D & p, Vector3D & d)
	{
		return PlaneIntersection(p1,p2, p, d);
	}
	bool Intersection::CheckIntersection(Plane p1, Plane p2, Plane p3, Vector3D & p)
	{
		return PlaneIntersection(p1,p2,p3,p);
	}
	bool Intersection::CheckIntersection(Frustum f, Vector3D p)
	{
		return FrustrumNPointIntersection(f,p);
	}
	bool Intersection::CheckIntersection(Vector3D p, Frustum f)
	{
		return FrustrumNPointIntersection(f, p);
	}
	bool Intersection::CheckIntersection(Frustum f, Sphere s)
	{
		return FrustrumNSphereIntersection(f, s);
	}
	bool Intersection::CheckIntersection(Sphere s, Frustum f)
	{
		return FrustrumNSphereIntersection(f, s);
	}
	bool Intersection::CheckIntersection(Frustum f, AABB a)
	{
		return FrustumNAABBIntersection(f, a);
	}
	bool Intersection::CheckIntersection(AABB a, Frustum f)
	{
		return FrustumNAABBIntersection(f, a);
	}
	bool Intersection::SphereIntersection(Sphere a, Sphere b)
	{
		Vector3D distance = a.m_center - b.m_center;
		float dist2 = math::Dot(distance, distance);

		float radius = a.m_radius + b.m_radius;
		return dist2 <= radius * radius;
	}
	bool Intersection::OBBIntersection(OBB a, OBB b)
	{
		float ra, rb;
		Matrix3D R, absR;
		
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				R.Line[i][j] = math::Dot(a.m_axis[i], b.m_axis[j]);

		Vector3D transalte = b.m_position - a.m_position;
		transalte = Vector3D(math::Dot(transalte, a.m_axis[0]), math::Dot(transalte, a.m_axis[2]), math::Dot(transalte, a.m_axis[2]));

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				absR.Line[i][j] = math::Abs(R.Line[i][j]) + math::fEpsilon;

		for (int i = 0; i < 3; i++)
		{
			ra = a.m_dimentions[i];
			rb = b.m_dimentions[0] * absR.Line[i][0] + b.m_dimentions[1] * absR.Line[i][1] + b.m_dimentions[2] * absR.Line[i][2];
			if (math::Abs(transalte[i]) > ra + rb)
				return false;
		}

		for (int i = 0; i < 3; i++)
		{
			ra = a.m_dimentions[0] * absR.Line[0][i] + a.m_dimentions[1] * absR.Line[1][i] + b.m_dimentions[2] * absR.Line[2][i];
			rb = b.m_dimentions[i];
			float p = math::Abs(transalte[0] * R.Line[0][i] + transalte[1] * R.Line[1][i] + transalte[2] * R.Line[2][i]);
			float c = ra + rb;
			if (p > c)
				return false;
		}

		ra = a.m_dimentions[1] * absR.Line[2][0] + a.m_dimentions[2] * absR.Line[1][0];
		rb = b.m_dimentions[1] * absR.Line[0][2] + b.m_dimentions[2] * absR.Line[0][1];
		if (math::Abs(transalte[2] * R.Line[1][0] - transalte[1] * R.Line[2][0]) > ra + rb)
			return false;

		ra = a.m_dimentions[1] * absR.Line[2][1] + a.m_dimentions[2] * absR.Line[1][1];
		rb = b.m_dimentions[0] * absR.Line[0][2] + b.m_dimentions[2] * absR.Line[0][0];
		if (math::Abs(transalte[2] * R.Line[1][1] - transalte[1] * R.Line[2][1]) > ra + rb)
			return false;

		ra = a.m_dimentions[1] * absR.Line[2][2] + a.m_dimentions[2] * absR.Line[1][2];
		rb = b.m_dimentions[0] * absR.Line[0][1] + b.m_dimentions[1] * absR.Line[0][0];
		if (math::Abs(transalte[2] * R.Line[1][2] - transalte[1] * R.Line[2][2]) > ra + rb) 
			return false;

		ra = a.m_dimentions[0] * absR.Line[2][0] + a.m_dimentions[2] * absR.Line[0][0];
		rb = b.m_dimentions[1] * absR.Line[1][2] + b.m_dimentions[2] * absR.Line[1][1];
		if (math::Abs(transalte[0] * R.Line[2][0] - transalte[2] * R.Line[0][0]) > ra + rb) 
			return false;

		ra = a.m_dimentions[0] * absR.Line[2][1] + a.m_dimentions[2] * absR.Line[0][1];
		rb = b.m_dimentions[0] * absR.Line[1][2] + b.m_dimentions[2] * absR.Line[1][0];
		if (math::Abs(transalte[0] * R.Line[2][1] - transalte[2] * R.Line[0][1]) > ra + rb)
			return false;

		ra = a.m_dimentions[0] * absR.Line[2][2] + a.m_dimentions[2] * absR.Line[0][2];
		rb = b.m_dimentions[0] * absR.Line[1][1] + b.m_dimentions[1] * absR.Line[1][0];
		if (math::Abs(transalte[0] * R.Line[2][2] - transalte[2] * R.Line[0][2]) > ra + rb)
			return false;

		ra = a.m_dimentions[0] * absR.Line[1][0] + a.m_dimentions[1] * absR.Line[0][0];
		rb = b.m_dimentions[1] * absR.Line[2][2] + b.m_dimentions[2] * absR.Line[2][1];
		if (math::Abs(transalte[1] * R.Line[0][0] - transalte[0] * R.Line[1][0]) > ra + rb) 
			return false;

		ra = a.m_dimentions[0] * absR.Line[1][1] + a.m_dimentions[1] * absR.Line[0][1];
		rb = b.m_dimentions[0] * absR.Line[2][2] + b.m_dimentions[2] * absR.Line[2][0];
		if (math::Abs(transalte[1] * R.Line[0][1] - transalte[0] * R.Line[1][1]) > ra + rb) 
			return false;

		ra = a.m_dimentions[0] * absR.Line[1][2] + a.m_dimentions[1] * absR.Line[0][2];
		rb = b.m_dimentions[0] * absR.Line[2][1] + b.m_dimentions[1] * absR.Line[2][0];
		if (math::Abs(transalte[1] * R.Line[0][2] - transalte[0] * R.Line[1][2]) > ra + rb)
			return false;

		return true;
	}
	bool Intersection::SphereNOBBIntersection(Sphere s, OBB b)
	{
		Vector3D p;
		// Find point p on OBB closest to sphere center
		ClosestPtPointOBB(s.m_center, b, p);
		// Sphere and OBB intersect if the (squared) distance from sphere
		// center to point p is less than the (squared) sphere radius
		Vector3D v = p - s.m_center;

		if (math::Dot(v, v) <= s.m_radius * s.m_radius)
			return true;

		return false;
	}
	void Intersection::ClosestPtPointOBB(Vector3D p, OBB b, Vector3D & q)
	{
		Vector3D d = p - b.m_position;
		// Start result at center of box; make steps from there
		q = b.m_position;
		// For each OBB axis...
		for (int i = 0; i < 3; i++)
		{
			// ...project d onto that axis to get the distance
			// along the axis of d from the box center
			float dist = math::Dot(d, b.m_axis[i]);
			// If distance farther than the box extents, clamp to the box
			if (dist > b.m_dimentions[i]) dist = b.m_dimentions[i];
			if (dist < -b.m_dimentions[i]) dist = -b.m_dimentions[i];
			// Step that distance along the axis to get world coordinate
			q += b.m_axis[i] * dist;
		}
	}
	bool Intersection::RayNPlaneIntersection(Ray _ray, Plane _plane)
	{
		Vector3D ray = Vector3D(_ray.m_direction) * math::MAX_FLOAT_VALUE;

		Vector3D planeNormal = Vector3D(_plane.a, _plane.b, _plane.c);

		float t = (_plane.d - math::Dot(planeNormal, _ray.m_origin)) / math::Dot(planeNormal, ray);

		if (t >= 0.0f && t <= 1.0f)
		{
			return true;
		}
		return false;
	}
	bool Intersection::AABBIntersection(AABB _a, AABB _b)
	{
		if (_a.m_max.x < _b.m_min.x || _a.m_min.x > _b.m_max.x) 
			return false;
		if (_a.m_max.y < _b.m_min.y || _a.m_min.y > _b.m_max.y) 
			return false;
		if (_a.m_max.z < _b.m_min.z || _a.m_min.z > _b.m_max.z) 
			return false;

		return true;
	}
	bool Intersection::AABBNSphereIntersection(AABB _a, Sphere _s)
	{
		float sqDist = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			
			float v = _s.m_center[i];

			if (v < (_a.m_min[i] + _a.m_center[i]))
				sqDist += ((_a.m_min[i] + _a.m_center[i]) - v) * ((_a.m_min[i] + _a.m_center[i]) - v);

			if (v > (_a.m_max[i] + _a.m_center[i]))
				sqDist += (v - (_a.m_max[i] + _a.m_center[i])) * (v - (_a.m_max[i] + _a.m_center[i]));
		}

		if(sqDist <= _s.m_radius * _s.m_radius)
			return true;

		return false;
	}
	bool Intersection::PlaneIntersection(Plane p1, Plane p2, Vector3D & p, Vector3D & d)
	{
		// Compute direction of intersection line
		Vector3D p1n(p1.a, p1.b, p1.c);
		Vector3D p2n(p2.a, p2.b, p2.c);
		d = math::CrossProduct(p1n, p2n);
		// If d is zero, the planes are parallel (and separated)
		// or coincident, so they’re not considered intersecting
		if (math::Dot(d, d) < math::fEpsilon) 
			return false;

		float d11 = math::Dot(p1n, p1n);
		float d12 = math::Dot(p1n, p2n);
		float d22 = math::Dot(p2n, p2n);
		float denom = d11*d22 - d12*d12;
		float k1 = (p1.d*d22 - p2.d*d12) / denom;
		float k2 = (p2.d*d11 - p1.d*d12) / denom;
		p = p1n*k1 + p2n*k2;

		return true;
	}
	bool Intersection::PlaneIntersection(Plane p1, Plane p2, Plane p3, Vector3D & p)
	{
		Vector3D m1 = Vector3D(p1.a, p2.a, p3.a);
		Vector3D m2 = Vector3D(p1.b, p2.b, p3.b);
		Vector3D m3 = Vector3D(p1.c, p2.c, p3.c);

		Vector3D u = math::CrossProduct(m2, m3);
		float denom = math::Dot(m1, u);

		if (math::Abs(denom) < math::fEpsilon) 
			return false; // Planes do not intersect in a point

		Vector3D d(p1.d, p2.d, p3.d);
		Vector3D v = math::CrossProduct(m1, d);

		float ood = 1.0f / denom;
		p.x = math::Dot(d, u) * ood;
		p.y = math::Dot(m3, v) * ood;
		p.z = -math::Dot(m2, v) * ood;

		return true;
	}
	bool Intersection::FrustrumNPointIntersection(Frustum f, Vector3D p)
	{
		for (int i = 0; i < 6; i++)
		{
			if (f.m_planes[i].a * p.x + f.m_planes[i].b * p.y + f.m_planes[i].c * p.z + f.m_planes[i].d <= 0)
				return false;
		}
		return true;
	}
	bool Intersection::FrustrumNSphereIntersection(Frustum f, Sphere s)
	{
		for (int i = 0; i < 6; i++)
		{
			if (f.m_planes[i].a * s.m_center.x + f.m_planes[i].b * s.m_center.y + f.m_planes[i].c * s.m_center.z + f.m_planes[i].d <= -s.m_radius)
				return false;
		}
		return true;
	}
	bool Intersection::FrustumNAABBIntersection(Frustum f, AABB a)
	{
		float sizeX = a.m_max.x - a.m_min.x;
		float sizeY = a.m_max.y - a.m_min.y;
		float sizeZ = a.m_max.z - a.m_min.z;

		for (int i = 0; i < 6; i++)
		{
			if (f.m_planes[i].a * (a.m_center.x - sizeX) + f.m_planes[i].b * (a.m_center.y - sizeY) + f.m_planes[i].c * (a.m_center.z - sizeZ) + f.m_planes[i].d > 0)
				continue;
			if (f.m_planes[i].a * (a.m_center.x + sizeX) + f.m_planes[i].b * (a.m_center.y - sizeY) + f.m_planes[i].c * (a.m_center.z - sizeZ) + f.m_planes[i].d > 0)
				continue;
			if (f.m_planes[i].a * (a.m_center.x - sizeX) + f.m_planes[i].b * (a.m_center.y + sizeY) + f.m_planes[i].c * (a.m_center.z - sizeZ) + f.m_planes[i].d > 0)
				continue;
			if (f.m_planes[i].a * (a.m_center.x + sizeX) + f.m_planes[i].b * (a.m_center.y + sizeY) + f.m_planes[i].c * (a.m_center.z - sizeZ) + f.m_planes[i].d > 0)
				continue;
			if (f.m_planes[i].a * (a.m_center.x - sizeX) + f.m_planes[i].b * (a.m_center.y - sizeY) + f.m_planes[i].c * (a.m_center.z + sizeZ) + f.m_planes[i].d > 0)
				continue;
			if (f.m_planes[i].a * (a.m_center.x + sizeX) + f.m_planes[i].b * (a.m_center.y - sizeY) + f.m_planes[i].c * (a.m_center.z + sizeZ) + f.m_planes[i].d > 0)
				continue;
			if (f.m_planes[i].a * (a.m_center.x - sizeX) + f.m_planes[i].b * (a.m_center.y + sizeY) + f.m_planes[i].c * (a.m_center.z + sizeZ) + f.m_planes[i].d > 0)
				continue;
			if (f.m_planes[i].a * (a.m_center.x + sizeX) + f.m_planes[i].b * (a.m_center.y + sizeY) + f.m_planes[i].c * (a.m_center.z + sizeZ) + f.m_planes[i].d > 0)
				continue;

			return false;
		}
		return true;
	}
	Intersection::Intersection()
	{
	}


	Intersection::~Intersection()
	{
	}
}
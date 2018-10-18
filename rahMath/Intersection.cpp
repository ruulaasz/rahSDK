#include "Intersection.h"
#include "Vector3D.h"
#include "PlatformMath.h"

namespace rah
{
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
			if (math::Abs(transalte[0] * R.Line[0][i] + transalte[1] * R.Line[1][i] + transalte[2] * R.Line[2][i]) > ra + rb)
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
		if (math::Abs(transalte[1] * R.Line[0][2] - transalte[0] * R.Line[1][2]) > ra + rb)			return false;

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
	Intersection::Intersection()
	{
	}


	Intersection::~Intersection()
	{
	}
}
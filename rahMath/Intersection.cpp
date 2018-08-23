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


		return true;
	}
	Intersection::Intersection()
	{
	}


	Intersection::~Intersection()
	{
	}
}
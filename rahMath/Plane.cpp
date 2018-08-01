#include "Plane.h"
#include "PlatformMath.h"

namespace rah
{
	Plane::Plane()
	{

	}

	Plane::Plane(Vector3D _A, Vector3D _B, Vector3D _C)
	{
		initFromVectors(_A, _B, _C);
	}

	Plane::Plane(const Plane & _plane)
	{
		a = _plane.a;
		b = _plane.b;
		c = _plane.c;
		d = _plane.d;
	}

	Plane::~Plane()
	{

	}

	void Plane::render()
	{

	}

	void Plane::initFromVectors(Vector3D _A, Vector3D _B, Vector3D _C)
	{
		a = ((_B.y - _A.y) * (_C.z - _A.z)) - ((_C.y - _A.y) * (_B.z - _A.z));
		b = ((_B.z - _A.z) * (_C.x - _A.x)) - ((_C.z - _A.z) * (_B.x - _A.x));
		c = ((_B.x - _A.x) * (_C.y - _A.y)) - ((_C.x - _A.x) * (_B.y - _A.y));
		d = -((a * _A.x) + (b * _A.y) + (c * _A.z));
	}
}
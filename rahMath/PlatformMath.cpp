#include "PlatformMath.h"

namespace rah
{
	namespace math
	{
		float AbsVec3D(Vector3D _vec)
		{
			return Sqrt(Square(_vec.x) + Square(_vec.y) + Square(_vec.z));
		}
	}
}
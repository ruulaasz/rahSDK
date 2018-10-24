#pragma once

#include <rahTools.h>
#include <rahMath.h>

namespace rah
{


	struct GStruct
	{

	};

	class RenderManager : public rah::Module<RenderManager, GStruct>
	{
	public:
		RenderManager();
		~RenderManager();

		RahResult Initialize(GStruct ptr);

		void Release() {};

		void renderShape(const OBB& _obb);
		void renderShape(const AABB& _aabb);
		void renderShape(const Ray& _ray);
		void renderShape(const Sphere& _sphere, unsigned int _faces = 16);
		void renderShape(const Frustum& _frustum);
	};
}
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

		void renderShape(const OBB& _obb, Color _color);
	};
}
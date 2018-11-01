#pragma once

#include <rahTools.h>
#include <rahMath.h>
#include "ConstantBuffer.h"

namespace rah
{
	struct CBView
	{
		Matrix4D view;
	};

	struct CBProj
	{
		Matrix4D projection;
	};

	struct CBWorld
	{
		rah::Matrix4D mWorld;
	};

	struct CBColor
	{
		rah::Color mColor;
	};

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
		void renderGrid();

		void updateProjection();
		void updateView(const Matrix4D& _matrix);
		void updateWorld(const Matrix4D& _matrix);
		void updateColor(const Color& _color);

		ConstantBuffer m_cbView;
		ConstantBuffer m_cbProj;
		ConstantBuffer m_cbWorld;
		ConstantBuffer m_cbColor;

		ID3D11DeviceContext* m_deviceContext;

		Matrix4D m_view;
		Matrix4D m_projection;
		Matrix4D m_world;
		Color m_color;
	};
}
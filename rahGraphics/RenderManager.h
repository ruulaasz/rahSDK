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

		void renderShape(const OBB& _obb, Color _color = Color(1.f, 0.f, 0.f));
		void renderShape(const AABB& _aabb, Color _color = Color(1.f, 0.f, 0.f));
		void renderShape(const Ray& _ray, Color _color = Color(1.f, 0.f, 0.f));
		void renderShape(const Sphere& _sphere, unsigned int _faces = 16, Color _color = Color(1.f, 0.f, 0.f));
		void renderShape(const Frustum& _frustum);
		void renderShape(const Vector4D& _from, const Vector4D& _to, Color _color = Color(1.f, 0.f, 0.f));
		void renderGrid(int size = 100, int divitions = 80, Color _color = Color(0.5f, 0.5f, 0.5f));

		void updateProjection();
		void updateView(const Matrix4D& _matrix);
		void updateWorld(const Matrix4D& _matrix);
		void updateColor(const Color& _color);

		ConstantBuffer m_cbView;
		ConstantBuffer m_cbProj;
		ConstantBuffer m_cbWorld;
		ConstantBuffer m_cbColor;

		ID3D11DeviceContext* m_deviceContext;
		ID3D11SamplerState* m_samplerState;
		D3D11_VIEWPORT* m_viewport;

		Matrix4D m_view;
		Matrix4D m_projection;
		Matrix4D m_world;
		Color m_color;
	};
}
#include "RenderManager.h"
#include "RenderManager.h"
#include "GraphicManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <rahMath.h>

namespace rah
{
	RenderManager::RenderManager()
	{

	}

	RenderManager::~RenderManager()
	{

	}

	RahResult RenderManager::Initialize(GStruct /*ptr*/)
	{
		m_deviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CBView);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		m_cbView.create(&bd);
		m_deviceContext->VSSetConstantBuffers(0, 1, &m_cbView.m_buffer);

		bd.ByteWidth = sizeof(CBProj);
		m_cbProj.create(&bd, nullptr);
		m_deviceContext->VSSetConstantBuffers(1, 1, &m_cbProj.m_buffer);

		bd.ByteWidth = sizeof(CBWorld);
		m_cbWorld.create(&bd, nullptr);
		m_deviceContext->VSSetConstantBuffers(2, 1, &m_cbWorld.m_buffer);

		bd.ByteWidth = sizeof(CBColor);
		m_cbColor.create(&bd, nullptr);
		m_deviceContext->VSSetConstantBuffers(3, 1, &m_cbColor.m_buffer);

		float aspectRatio = float(GraphicManager::GetInstance().m_width) / float(GraphicManager::GetInstance().m_height);
		m_projection = math::PerspectiveFovLH(math::PI / 4, aspectRatio, 0.01f, 100.0f);

		// Create and set the sample state
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr())->CreateSamplerState(&sampDesc, &m_samplerState);
		m_deviceContext->PSSetSamplers(0, 1, &m_samplerState);

		m_deviceContext->OMSetDepthStencilState(rah::GraphicManager::GetInstance().m_depthStencilState, 1);

		m_deviceContext->RSSetViewports(1, reinterpret_cast<D3D11_VIEWPORT*>(rah::GraphicManager::GetInstance().m_viewport.getPtr()));

		return RahResult();
	}

	void RenderManager::updateProjection()
	{
		CBProj cbproj;
		cbproj.projection = math::Transpose(m_projection);
		m_deviceContext->UpdateSubresource(m_cbProj.m_buffer, 0, NULL, &cbproj, 0, 0);
	}

	void RenderManager::updateView(const Matrix4D & _matrix)
	{
		m_view = _matrix;

		CBView cbview;
		cbview.view = math::Transpose(m_view);
		m_deviceContext->UpdateSubresource(m_cbView.m_buffer, 0, NULL, &cbview, 0, 0);
	}

	void RenderManager::updateWorld(const Matrix4D & _matrix)
	{
		m_world = _matrix;

		CBWorld cbWorld;
		cbWorld.mWorld = m_world;
		m_deviceContext->UpdateSubresource(m_cbWorld.m_buffer, 0, NULL, &cbWorld, 0, 0);
	}

	void RenderManager::updateColor(const Color & _color)
	{
		m_color = _color;

		CBColor cbColor;
		cbColor.mColor = m_color;
		m_deviceContext->UpdateSubresource(m_cbColor.m_buffer, 0, NULL, &cbColor, 0, 0);
	}

	void RenderManager::renderShape(const OBB & _obb, Color _color)
	{
		Matrix4D g_Scale;
		Matrix4D g_Translation;
		Matrix4D g_Rotation;

		g_Scale = rah::math::ScalarMatrix4x4(_obb.m_dimentions.x, _obb.m_dimentions.y, _obb.m_dimentions.z);

		g_Rotation = rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[0].x).getRadians(), rah::math::Axis_X);
		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[0].y).getRadians(), rah::math::Axis_X);
		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[0].z).getRadians(), rah::math::Axis_X);

		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[1].x).getRadians(), rah::math::Axis_Y);
		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[1].y).getRadians(), rah::math::Axis_Y);
		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[1].z).getRadians(), rah::math::Axis_Y);

		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[2].x).getRadians(), rah::math::Axis_Z);
		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[2].y).getRadians(), rah::math::Axis_Z);
		g_Rotation = g_Rotation * rah::math::RotationMatrix4x4(rah::Degrees(_obb.m_axis[2].z).getRadians(), rah::math::Axis_Z);

		g_Translation = rah::math::TranslationMatrix4x4(_obb.m_position.x, _obb.m_position.y, _obb.m_position.z);

		rah::RenderManager::GetInstance().updateWorld(g_Scale * g_Rotation * g_Translation);
		rah::RenderManager::GetInstance().updateColor(_color);

		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		//vertex buffer
		VertexBuffer vertexBuffer;
		VertexData myVertex;

		myVertex.pos = Vector4D(-1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);

		myVertex.pos = Vector4D(-1.f, 1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, -1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, -1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);

		vertexBuffer.create();

		//index buffer
		IndexBuffer indexBuffer;

		indexBuffer.addIndex(0);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(2);

		indexBuffer.addIndex(2);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(3);

		indexBuffer.addIndex(4);
		indexBuffer.addIndex(0);
		indexBuffer.addIndex(6);

		indexBuffer.addIndex(6);
		indexBuffer.addIndex(0);
		indexBuffer.addIndex(2);

		indexBuffer.addIndex(7);
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(6);

		indexBuffer.addIndex(6);
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(4);

		indexBuffer.addIndex(3);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(7);

		indexBuffer.addIndex(7);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(5);

		indexBuffer.addIndex(4);
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(0);

		indexBuffer.addIndex(0);
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(1);

		indexBuffer.addIndex(3);
		indexBuffer.addIndex(7);
		indexBuffer.addIndex(2);

		indexBuffer.addIndex(2);
		indexBuffer.addIndex(7);
		indexBuffer.addIndex(6);

		indexBuffer.create();

		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		m_deviceContext->IASetIndexBuffer(indexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->RSSetState(GraphicManager::GetInstance().m_rasterizerState[1]);
		m_deviceContext->DrawIndexed(indexBuffer.getIndexSize(), 0, 0);
	}

	void RenderManager::renderShape(const AABB & _aabb, Color _color)
	{
		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}
		AABB aabb = _aabb;
		aabb.m_max += aabb.m_center;
		aabb.m_max.w = 1.f;
		aabb.m_min += aabb.m_center;
		aabb.m_min.w = 1.f;

		renderShape(aabb.m_min, Vector4D(aabb.m_min.x, aabb.m_min.y, aabb.m_max.z), _color);
		renderShape(Vector4D(aabb.m_min.x, aabb.m_min.y, aabb.m_max.z), Vector4D(aabb.m_max.x, aabb.m_min.y, aabb.m_max.z), _color);
		renderShape(Vector4D(aabb.m_max.x, aabb.m_min.y, aabb.m_max.z), Vector4D(aabb.m_max.x, aabb.m_min.y, aabb.m_min.z), _color);
		renderShape(Vector4D(aabb.m_max.x, aabb.m_min.y, aabb.m_min.z), aabb.m_min, _color);

		renderShape(aabb.m_max, Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z), _color);
		renderShape(aabb.m_max, Vector4D(aabb.m_max.x, aabb.m_max.y, aabb.m_min.z), _color);
		renderShape(Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z), Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z), _color);
		renderShape(Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z), Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z), _color);

		renderShape(Vector4D(aabb.m_max.x, aabb.m_max.y, aabb.m_min.z), Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_min.z), _color);
		renderShape(aabb.m_max, Vector4D(aabb.m_max.x, aabb.m_min.y, aabb.m_max.z), _color);
		renderShape(aabb.m_min, Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_min.z), _color);
		renderShape(Vector4D(aabb.m_max.x, aabb.m_max.y, aabb.m_min.z), Vector4D(aabb.m_max.x, aabb.m_min.y, aabb.m_min.z), _color);

		renderShape(Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z), Vector4D(aabb.m_min.x, aabb.m_min.y, aabb.m_max.z), _color);
		renderShape(Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_max.z), Vector4D(aabb.m_min.x, aabb.m_max.y, aabb.m_min.z), _color);
	}

	void RenderManager::renderShape(const Ray & _ray, Color _color)
	{
		updateWorld(math::Identity4D());
		updateColor(_color);

		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		//vertex buffer
		VertexBuffer vertexBuffer;
		VertexData myVertex;

		myVertex.pos = Vector4D(_ray.m_origin);
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(_ray.m_direction) * 20;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		vertexBuffer.create();

		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		m_deviceContext->RSSetState(GraphicManager::GetInstance().m_rasterizerState[1]);
		m_deviceContext->Draw(vertexBuffer.getVertexSize(), 0);
	}

	void RenderManager::renderShape(const Sphere & _sphere, unsigned int _faces, Color _color)
	{
		rah::RenderManager::GetInstance().updateColor(_color);

		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		float jumpAngle = math::DOUBLE_PI / _faces;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		int lastIndex = 0;
		for (size_t i = 0; i < _faces; i++)
		{
			float CurrentRadio = math::Cos(jumpAngle * i) * _sphere.m_radius;
			float NextRadio = math::Cos(jumpAngle * (i + 1)) * _sphere.m_radius;

			VertexData v1, v2, v3;
			v1.pos.y = (math::Sin(jumpAngle * i) * _sphere.m_radius) + _sphere.m_center.y;
			v2.pos.y = v1.pos.y;

			if (i != _faces - 1)
			{
				v3.pos.y = (math::Sin(jumpAngle * (i + 1)) * _sphere.m_radius) + _sphere.m_center.y;
			}
			else
			{
				v3.pos.y = (math::Sin(jumpAngle * 0) * _sphere.m_radius) + _sphere.m_center.y;
			}

			for (size_t j = 0; j < _faces; j++)
			{
				v1.pos.x = (math::Cos(jumpAngle * j) * CurrentRadio) + _sphere.m_center.x;
				v1.pos.z = (math::Sin(jumpAngle * j) * CurrentRadio) + _sphere.m_center.z;
				v1.pos.w = 1.0f;

				v3.pos.x = (math::Cos(jumpAngle * j) * NextRadio) + _sphere.m_center.x;
				v3.pos.z = (math::Sin(jumpAngle * j) * NextRadio) + _sphere.m_center.z;
				v3.pos.w = 1.0f;

				if (j != _faces - 1)
				{
					v2.pos.x = (math::Cos(jumpAngle * (j + 1)) * CurrentRadio) + _sphere.m_center.x;
					v2.pos.z = (math::Sin(jumpAngle * (j + 1)) * CurrentRadio) + _sphere.m_center.z;
					v2.pos.w = 1.0f;
				}
				else
				{
					v2.pos.x = (math::Cos(jumpAngle * 0) * CurrentRadio) + _sphere.m_center.x;
					v2.pos.z = (math::Sin(jumpAngle * 0) * CurrentRadio) + _sphere.m_center.z;
					v2.pos.w = 1.0f;
				}

				vertexBuffer.addVertex(v1);
				indexBuffer.addIndex(lastIndex);
				vertexBuffer.addVertex(v2);
				indexBuffer.addIndex((lastIndex + 1));
				vertexBuffer.addVertex(v3);
				indexBuffer.addIndex((lastIndex + 2));
				lastIndex = (lastIndex + 2);
			}
		}

		vertexBuffer.create();
		indexBuffer.create();
		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		m_deviceContext->RSSetState(GraphicManager::GetInstance().m_rasterizerState[1]);
		m_deviceContext->Draw(vertexBuffer.getVertexSize(), 0);
	}

	void RenderManager::renderShape(const Frustum & _frustum)
	{
		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		//vertex buffer
		VertexBuffer vertexBuffer;
		VertexData myVertex;
		Vector3D p;

		Intersection::CheckIntersection(_frustum.m_planes[TOP], _frustum.m_planes[LEFT], _frustum.m_planes[FRONT], p);//0
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		Intersection::CheckIntersection(_frustum.m_planes[TOP], _frustum.m_planes[RIGHT], _frustum.m_planes[FRONT], p);//1
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		Intersection::CheckIntersection(_frustum.m_planes[BOTTOM], _frustum.m_planes[RIGHT], _frustum.m_planes[FRONT], p);//2
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		Intersection::CheckIntersection(_frustum.m_planes[BOTTOM], _frustum.m_planes[LEFT], _frustum.m_planes[FRONT], p);//3
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		Intersection::CheckIntersection(_frustum.m_planes[BOTTOM], _frustum.m_planes[LEFT], _frustum.m_planes[BACK], p);//4
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		Intersection::CheckIntersection(_frustum.m_planes[BOTTOM], _frustum.m_planes[RIGHT], _frustum.m_planes[BACK], p);//5
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		Intersection::CheckIntersection(_frustum.m_planes[TOP], _frustum.m_planes[RIGHT], _frustum.m_planes[BACK], p);//6
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		Intersection::CheckIntersection(_frustum.m_planes[TOP], _frustum.m_planes[LEFT], _frustum.m_planes[BACK], p);//7
		myVertex.pos = p;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		vertexBuffer.create();

		IndexBuffer indexBuffer;

		//front
		indexBuffer.addIndex(0);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(3);

		indexBuffer.addIndex(3);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(2);

		//top
		indexBuffer.addIndex(0);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(7);

		indexBuffer.addIndex(7);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(6);

		//back
		indexBuffer.addIndex(7);
		indexBuffer.addIndex(6);
		indexBuffer.addIndex(4);

		indexBuffer.addIndex(4);
		indexBuffer.addIndex(6);
		indexBuffer.addIndex(5);

		//right
		indexBuffer.addIndex(6);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(5);

		indexBuffer.addIndex(5);
		indexBuffer.addIndex(1);
		indexBuffer.addIndex(2);

		//left
		indexBuffer.addIndex(0);
		indexBuffer.addIndex(7);
		indexBuffer.addIndex(4);

		indexBuffer.addIndex(4);
		indexBuffer.addIndex(7);
		indexBuffer.addIndex(3);

		//bottom
		indexBuffer.addIndex(2);
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(4);

		indexBuffer.addIndex(4);
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(3);

		indexBuffer.create();

		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		m_deviceContext->IASetIndexBuffer(indexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->RSSetState(GraphicManager::GetInstance().m_rasterizerState[1]);
		m_deviceContext->DrawIndexed(indexBuffer.getIndexSize(), 0, 0);
	}

	void RenderManager::renderShape(const Vector4D & _from, const Vector4D & _to, Color _color)
	{
		updateWorld(math::Identity4D());
		updateColor(_color);

		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		//vertex buffer
		VertexBuffer vertexBuffer;
		VertexData myVertex;

		myVertex.pos = _from;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = _to;
		myVertex.pos.w = 1.f;
		vertexBuffer.addVertex(myVertex);

		vertexBuffer.create();

		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		m_deviceContext->RSSetState(GraphicManager::GetInstance().m_rasterizerState[1]);
		m_deviceContext->Draw(vertexBuffer.getVertexSize(), 0);
		vertexBuffer.m_buffer->Release();
	}

	void RenderManager::renderGrid(int _size, int _divitions, Color _color)
	{
		Matrix4D g_Scale;
		Matrix4D g_Translation;
		Matrix4D g_Rotation;

		g_Scale = math::ScalarMatrix4x4((float)_size, (float)_size, (float)_size);

		g_Rotation = math::Identity4D();

		g_Translation = math::Identity4D();

		updateWorld(g_Scale * g_Rotation * g_Translation);

		updateColor(_color);

		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		//vertex buffer
		VertexBuffer vertexBuffer;
		VertexData myVertex;

		Vector3D xaxis(2.f, 0.f, 0.f);
		Vector3D yaxis(0.f, 0.f, 2.f);
		Vector3D origin;

		size_t divisions = _divitions;

		for (size_t i = 0; i <= divisions; ++i)
		{
			float fPercent = float(i) / float(divisions);
			fPercent = (fPercent * 2.0f) - 1.0f;

			Vector3D scale = xaxis * fPercent + origin;

			myVertex.pos = scale - yaxis;
			myVertex.pos.w = 1.f;
			vertexBuffer.addVertex(myVertex);

			myVertex.pos = scale + yaxis;
			myVertex.pos.w = 1.f;
			vertexBuffer.addVertex(myVertex);
		}

		for (size_t i = 0; i <= divisions; ++i)
		{
			float fPercent = float(i) / float(divisions);
			fPercent = (fPercent * 2.0f) - 1.0f;

			Vector3D scale = yaxis * fPercent + origin;

			myVertex.pos = scale - xaxis;
			myVertex.pos.w = 1.f;
			vertexBuffer.addVertex(myVertex);

			myVertex.pos = scale + xaxis;
			myVertex.pos.w = 1.f;
			vertexBuffer.addVertex(myVertex);
		}

		vertexBuffer.create();

		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		m_deviceContext->Draw(vertexBuffer.getVertexSize(), 0);
		vertexBuffer.m_buffer->Release();
	}
}
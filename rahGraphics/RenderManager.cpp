#include "RenderManager.h"
#include "RenderManager.h"
#include "GraphicManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace rah
{
	RenderManager::RenderManager()
	{

	}

	RenderManager::~RenderManager()
	{

	}

	RahResult RenderManager::Initialize(GStruct ptr)
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

	void RenderManager::renderShape(const OBB & _obb)
	{
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

	void RenderManager::renderShape(const AABB & _aabb)
	{
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

	void RenderManager::renderShape(const Ray & _ray)
	{
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

	void RenderManager::renderShape(const Sphere & _sphere, unsigned int _faces)
	{
		if (!m_deviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		float jumpAngle = math::DOUBLE_PI / _faces;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		int lastIndex = 0;
		for (int i = 0; i < _faces; i++)
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

			for (int j = 0; j < _faces; j++)
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

	void RenderManager::renderGrid()
	{
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

		size_t divisions = 80;

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
	}
}
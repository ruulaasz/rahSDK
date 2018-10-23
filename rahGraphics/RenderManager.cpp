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
		return RahResult();
	}

	void rah::RenderManager::renderShape(const OBB & _obb)
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		if (!pDeviceContext)
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
		pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(indexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pDeviceContext->DrawIndexed(indexBuffer.getIndexSize(), 0, 0);
	}

	void RenderManager::renderShape(const AABB & _aabb)
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		if (!pDeviceContext)
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
		pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(indexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		pDeviceContext->RSSetState(rah::GraphicManager::GetInstance().m_rasterizerState[1]);
		pDeviceContext->DrawIndexed(indexBuffer.getIndexSize(), 0, 0);
	}

	void RenderManager::renderShape(const Ray & _ray)
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		if (!pDeviceContext)
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
		pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		pDeviceContext->Draw(vertexBuffer.getVertexSize(), 0);
	}

	void RenderManager::renderShape(const Sphere & _sphere, unsigned int _faces)
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		if (!pDeviceContext)
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
		pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		//pDeviceContext->IASetIndexBuffer(indexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		//pDeviceContext->DrawIndexed(indexBuffer.getIndexSize(), 0, 0);
		pDeviceContext->Draw(vertexBuffer.getVertexSize(),0);
	}
}
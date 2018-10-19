#include "RenderManager.h"
#include "GraphicManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

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

	void RenderManager::renderShape(const Sphere & _sphere)
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		if (!pDeviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		//vertex buffer
		VertexBuffer vertexBuffer;
		VertexData myVertex;

		//1
		myVertex.pos = Vector4D(-1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, -1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, 1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);

		//2
		myVertex.pos = Vector4D(-1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);

		//3
		myVertex.pos = Vector4D(-1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, 1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);

		//4
		myVertex.pos = Vector4D(-1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, -1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, -1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);

		//5
		myVertex.pos = Vector4D(1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, -1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(1.f, 1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);

		//6
		myVertex.pos = Vector4D(-1.f, -1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, -1.f, 1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, 1.f, -1.f, 1.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-1.f, 1.f, 1.f, 1.f);
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
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(6);

		indexBuffer.addIndex(6);
		indexBuffer.addIndex(5);
		indexBuffer.addIndex(7);

		indexBuffer.addIndex(8);
		indexBuffer.addIndex(9);
		indexBuffer.addIndex(10);

		indexBuffer.addIndex(10);
		indexBuffer.addIndex(9);
		indexBuffer.addIndex(11);

		indexBuffer.addIndex(12);
		indexBuffer.addIndex(13);
		indexBuffer.addIndex(14);

		indexBuffer.addIndex(14);
		indexBuffer.addIndex(13);
		indexBuffer.addIndex(15);

		indexBuffer.addIndex(16);
		indexBuffer.addIndex(17);
		indexBuffer.addIndex(18);

		indexBuffer.addIndex(18);
		indexBuffer.addIndex(17);
		indexBuffer.addIndex(19);

		indexBuffer.addIndex(20);
		indexBuffer.addIndex(21);
		indexBuffer.addIndex(22);

		indexBuffer.addIndex(22);
		indexBuffer.addIndex(21);
		indexBuffer.addIndex(23);

		indexBuffer.create();

		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.m_buffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(indexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pDeviceContext->DrawIndexed(indexBuffer.getIndexSize(), 0, 0);

	
	}
}
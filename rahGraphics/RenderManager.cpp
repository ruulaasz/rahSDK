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

	void rah::RenderManager::renderShape(const OBB & _obb, Color _color)
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		if (!pDeviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		//vertex buffer
		VertexBuffer vertexBuffer;
		VertexData myVertex;

		float x = _obb.m_position.x + _obb.m_dimentions.x;
		float y = _obb.m_position.y + _obb.m_dimentions.y;
		float z = _obb.m_position.z + _obb.m_dimentions.z;

		myVertex.pos = Vector4D(-x, y, -z, 0.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(x, y, -z, 0.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-x, -y, -z, 0.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(x, -y, -z, 0.f);
		vertexBuffer.addVertex(myVertex);

		myVertex.pos = Vector4D(-x, y, z, 0.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(x, y, z, 0.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(-x, -y, z, 0.f);
		vertexBuffer.addVertex(myVertex);
		myVertex.pos = Vector4D(x, -y, z, 0.f);
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
}
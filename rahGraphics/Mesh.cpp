#include "Mesh.h"
#include "GraphicManager.h"

namespace rah
{
	Mesh::Mesh()
	{
		m_material = nullptr;
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::render()
	{
		ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(GraphicManager::GetInstance().m_deviceContext.getPtr());

		if (!pDeviceContext)
		{
			throw "NullPointer pDeviceContext";
		}

		pDeviceContext->PSSetShaderResources(0, 12, m_material->m_textures);

		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer.m_buffer, &stride, &offset);
		pDeviceContext->IASetIndexBuffer(m_indexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pDeviceContext->DrawIndexed(m_indexBuffer.getIndexSize(), 0, 0);
	}

	void Mesh::assignNewTexture(const GraphicTexture* _texture, TextureType _textureType)
	{
		if (!_texture)
		{
			throw "NullPointer _texture";
		}

		m_material->m_textures[_textureType] = _texture->m_graphicTexture;
	}

	void Mesh::assignNewMaterial(Material * _material)
	{
		if (!_material)
		{
			throw "NullPointer _material";
		}

		m_material = _material;
	}
}
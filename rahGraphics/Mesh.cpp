#include "Mesh.h"
#include "GraphicManager.h"
#include <Importer.hpp>
#include <postprocess.h>
#include <scene.h>

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

		pDeviceContext->RSSetState(rah::GraphicManager::GetInstance().m_rasterizerState[2]);

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

	RahResult Mesh::Load()
	{
		std::string texturesPath = m_filePath.Get();
		VertexData myVertex;
		Mesh* pMesh = new Mesh();

		ID3D11Device* pD3DDevice = NULL;
		pD3DDevice = reinterpret_cast<ID3D11Device*>(GraphicManager::GetInstance().m_device.getPtr());

		Assimp::Importer g_importer;
		const aiScene* g_scene;

		g_scene = g_importer.ReadFile(texturesPath, aiProcess_ConvertToLeftHanded);

		if (!g_scene || !g_scene->HasMeshes())
		{
			throw "NullPointer g_scene";
		}

		for (size_t i = texturesPath.size() - 1; i >= 0; i--)
		{
			if (texturesPath.at(i) == '/' || texturesPath.at(i) == '\\')
				break;

			texturesPath.pop_back();
		}

		bool hasMaterials = g_scene->HasMaterials();

		if (g_scene->mMeshes[0]->HasPositions())
		{
			for (size_t j = 0; j < g_scene->mMeshes[0]->mNumVertices; ++j)
			{
				aiMesh* paiMesh = g_scene->mMeshes[0];

				myVertex.pos.x = paiMesh->mVertices[j].x;
				myVertex.pos.y = paiMesh->mVertices[j].y;
				myVertex.pos.z = paiMesh->mVertices[j].z;
				myVertex.pos.w = 1;

				if (g_scene->mMeshes[0]->HasNormals())
				{
					myVertex.norm.x = paiMesh->mNormals[j].x;
					myVertex.norm.y = paiMesh->mNormals[j].y;
					myVertex.norm.z = paiMesh->mNormals[j].z;
				}

				if (g_scene->mMeshes[0]->HasTextureCoords(0))
				{
					myVertex.tex.x = paiMesh->mTextureCoords[0][j].x;
					myVertex.tex.y = paiMesh->mTextureCoords[0][j].y;
				}

				pMesh->m_vertexBuffer.addVertex(myVertex);
			}

			pMesh->m_vertexBuffer.create();

			Material* pMaterial = new Material();

			if (hasMaterials)
			{
				aiString pPath;

				for (size_t k = 1; k < 12; ++k)
				{
					g_scene->mMaterials[g_scene->mMeshes[0]->mMaterialIndex]->GetTexture((aiTextureType)k, 0, &pPath);

					if (pPath.length > 0)
					{
						std::string textureName;
						std::string temp = pPath.C_Str();

						for (unsigned int j = temp.size() - 1; j >= 0; --j)
						{
							if (temp.at(j) == '/' || temp.at(j) == '\\')
								break;

							textureName.push_back(temp.at(j));
						}

						std::string finalPath = texturesPath;

						size_t j = textureName.size() - 1;
						for (; j >= 0; j--)
						{
							if (textureName.at(j) == '.')
								break;

							finalPath.push_back(textureName.at(j));
						}

						finalPath += ".dds";

						// Load the Texture
						GraphicTexture* newTexture = new GraphicTexture();
						rah::BasicResourceParams* rParams = new rah::BasicResourceParams();
						rParams->filePath = finalPath;
						newTexture->Initialize(rParams);
						newTexture->Load();

						pMaterial->m_textures[k] = newTexture->m_graphicTexture;
					}
				}
			}

			pMesh->m_material = pMaterial;
		}

		if (g_scene->mMeshes[0]->HasFaces())
		{
			for (size_t j = 0; j < g_scene->mMeshes[0]->mNumFaces; ++j)
			{
				for (size_t k = 0; k < g_scene->mMeshes[0]->mFaces->mNumIndices; k++)
				{
					pMesh->m_indexBuffer.addIndex(g_scene->mMeshes[0]->mFaces[j].mIndices[k]);
				}
			}

			pMesh->m_indexBuffer.create();
		}

		return RAH_SUCCESS;
	}
	void Mesh::Release()
	{
	}
}
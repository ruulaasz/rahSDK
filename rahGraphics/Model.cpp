#include "Model.h"
#include "Model.h"
#include <Importer.hpp>
#include <postprocess.h>
#include <scene.h>
#include "RenderManager.h"

namespace rah
{
	Model::Model()
	{
		m_renderDebug = true;
	}

	Model::~Model()
	{

	}

	void Model::assignMeshMaterial(Material* _material, unsigned int _index)
	{
		if (!_material)
		{
			throw "NullPointer _material";
		}

		if (_index >= 0 && _index < m_meshes.size())
		{
			m_meshes.at(_index)->assignNewMaterial(_material);
		}
	}

	void Model::assignMeshTexture(GraphicTexture * _texture, TextureType _textureType, unsigned int _index)
	{
		if (!_texture)
		{
			throw "NullPointer _texture";
		}

		if (_index >= 0 && _index < m_meshes.size())
		{
			m_meshes.at(_index)->assignNewTexture(_texture, _textureType);
		}
	}

	void Model::render()
	{
		for (UINT i = 0; i < m_meshes.size(); i++)
		{
			m_meshes.at(i)->render();
		}

		if (m_renderDebug)
		{
			RenderManager::GetInstance().renderShape(m_boundingBox);
		}
	}

	RahResult Model::Load()
	{
		std::string texturesPath = m_filePath.Get();
		VertexData myVertex;

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

		m_meshes.resize(g_scene->mNumMeshes);

		bool hasMaterials = g_scene->HasMaterials();

		for (size_t i = 0; i < g_scene->mNumMeshes; ++i)
		{
			m_meshes[i] = new Mesh();

			if (g_scene->mMeshes[i]->HasPositions())
			{
				for (size_t j = 0; j < g_scene->mMeshes[i]->mNumVertices; ++j)
				{
					aiMesh* paiMesh = g_scene->mMeshes[i];

					myVertex.pos.x = paiMesh->mVertices[j].x;
					myVertex.pos.y = paiMesh->mVertices[j].y;
					myVertex.pos.z = paiMesh->mVertices[j].z;
					myVertex.pos.w = 1;

					if (g_scene->mMeshes[i]->HasNormals())
					{
						myVertex.norm.x = paiMesh->mNormals[j].x;
						myVertex.norm.y = paiMesh->mNormals[j].y;
						myVertex.norm.z = paiMesh->mNormals[j].z;
					}

					if (g_scene->mMeshes[i]->HasTextureCoords(0))
					{
						myVertex.tex.x = paiMesh->mTextureCoords[0][j].x;
						myVertex.tex.y = paiMesh->mTextureCoords[0][j].y;
					}

					m_meshes[i]->m_vertexBuffer.addVertex(myVertex);
				}

				m_meshes[i]->m_vertexBuffer.create();

				Material* pMaterial = new Material();

				if (hasMaterials)
				{
					aiString pPath;

					for (size_t k = 1; k < 12; ++k)
					{
						g_scene->mMaterials[g_scene->mMeshes[i]->mMaterialIndex]->GetTexture((aiTextureType)k, 0, &pPath);

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

				m_meshes[i]->m_material = pMaterial;
			}

			if (g_scene->mMeshes[i]->HasFaces())
			{
				for (size_t j = 0; j < g_scene->mMeshes[i]->mNumFaces; ++j)
				{
					m_triangles.push_back(new Triangle);

					for (size_t k = 0; k < g_scene->mMeshes[i]->mFaces->mNumIndices; k++)
					{
						m_meshes[i]->m_indexBuffer.addIndex(g_scene->mMeshes[i]->mFaces[j].mIndices[k]);

						m_triangles.back()->m_Vertex->pos.x = g_scene->mMeshes[i]->mVertices[g_scene->mMeshes[i]->mFaces[j].mIndices[k]].x;
						m_triangles.back()->m_Vertex->pos.y = g_scene->mMeshes[i]->mVertices[g_scene->mMeshes[i]->mFaces[j].mIndices[k]].y;
						m_triangles.back()->m_Vertex->pos.z = g_scene->mMeshes[i]->mVertices[g_scene->mMeshes[i]->mFaces[j].mIndices[k]].z;
					}
				}

				m_meshes[i]->m_indexBuffer.create();
			}
		}

		setBox();

		return RahResult();
	}

	void Model::Release()
	{

	}

	void Model::setBox()
	{
		m_boundingBox.m_min = m_boundingBox.m_max = m_triangles.back()->m_Vertex->pos;

		for (int i = 0; i < m_triangles.size(); i++)
		{
			//Min
			if (m_triangles.at(i)->m_Vertex->pos.x < m_boundingBox.m_min.x)
			{
				m_boundingBox.m_min.x = m_triangles.at(i)->m_Vertex->pos.x;
			}

			if (m_triangles.at(i)->m_Vertex->pos.y < m_boundingBox.m_min.y)
			{
				m_boundingBox.m_min.y = m_triangles.at(i)->m_Vertex->pos.y;
			}

			if (m_triangles.at(i)->m_Vertex->pos.z < m_boundingBox.m_min.z)
			{
				m_boundingBox.m_min.z = m_triangles.at(i)->m_Vertex->pos.z;
			}

			//Max
			if (m_triangles.at(i)->m_Vertex->pos.x > m_boundingBox.m_max.x)
			{
				m_boundingBox.m_max.x = m_triangles.at(i)->m_Vertex->pos.x;
			}

			if (m_triangles.at(i)->m_Vertex->pos.y > m_boundingBox.m_max.y)
			{
				m_boundingBox.m_max.y = m_triangles.at(i)->m_Vertex->pos.y;
			}

			if (m_triangles.at(i)->m_Vertex->pos.z > m_boundingBox.m_max.z)
			{
				m_boundingBox.m_max.z = m_triangles.at(i)->m_Vertex->pos.z;
			}
		}

		Vector4D Temp;

		Temp = m_boundingBox.m_max - m_boundingBox.m_min;
		Temp /= 2;

		m_boundingBox.m_center = Temp + m_boundingBox.m_min;
	}
}
#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include <rahResource.h>
#include "GraphicTexture.h"

namespace rah
{
	/**
	* Container for a mesh object
	*/
	class Mesh : public rahResource
	{
	public:
		Mesh();
		~Mesh();

		/**
		* Render the mesh
		*
		* @param _immediateContext
		* Reference to a graphic device context
		*
		*/
		void render();

		/**
		* Assign a new texture
		*
		* @param _texture
		* Reference to a new texture
		*
		* @param _textureType = TextureType_DIFFUSE
		* The type of the new texture
		*
		*/
		void assignNewTexture(const GraphicTexture* _texture, TextureType _textureType = TextureType_DIFFUSE);

		/**
		* Assign a new material to the mesh
		*
		* @param _material
		* Reference to a new material
		*
		*/
		void assignNewMaterial(Material* _material);

		/*
		* Load is the obigatory function this should be called after initialize or during this
		*
		*/
		virtual RahResult Load();

		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
		Material* m_material;
	};
}
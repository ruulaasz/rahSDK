#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "GraphicTexture.h"

namespace rah
{
	class GraphicDeviceContext;
	/**
	* Container for a mesh object
	*/
	class Mesh
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
		void render(const GraphicDeviceContext* _immediateContext);

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
		void assignNewTexture(const Texture* _texture, TextureType _textureType = TextureType_DIFFUSE);

		/**
		* Assign a new material to the mesh
		*
		* @param _material
		* Reference to a new material
		*
		*/
		void assignNewMaterial(Material* _material);

		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
		Material* m_material;
	};
}
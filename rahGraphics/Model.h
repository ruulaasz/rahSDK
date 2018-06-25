#pragma once

#include "Mesh.h"
#include <vector>

namespace rah
{
	/**
	* Container for a model object
	*/
	class Model
	{
	public:
		Model();
		~Model();

		/**
		* Assign a new material to a mesh
		*
		* @param _material
		* Reference to a new material
		*
		* @param _index
		* The index of the mesh recieving the material
		*
		*/
		void assignMeshMaterial(Material* _material, unsigned int _index);

		/**
		* Assign a new texture to a mesh
		*
		* @param _texture
		* Reference to a new texture
		*
		* @param _textureType
		* The type of the new texture
		*
		* @param _index
		* The index of the mesh recieving the material
		*
		*/
		void assignMeshTexture(GraphicTexture* _texture, TextureType _textureType, unsigned int _index);

		/**
		* Render the model
		*
		* @param _immediateContext
		* Reference to a graphic device context
		*
		*/
		void render();

		std::vector <Mesh* > m_meshes;
		Matrix4D m_transform;
	};
}
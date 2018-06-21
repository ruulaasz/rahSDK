#pragma once

#include <vector>
#include "Mesh.h"

using std::vector;

namespace rah
{
	class GraphicDeviceContext;

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
		void assignMeshTexture(Texture* _texture, TextureType _textureType, unsigned int _index);

		/**
		* Render the model
		*
		* @param _immediateContext
		* Reference to a graphic device context
		*
		*/
		void render(const GraphicDeviceContext* _immediateContext);

		void Load() {};
		void Unload() {};

		vector <Mesh* > m_meshes;
		Matrix4D m_transform;
	};
}
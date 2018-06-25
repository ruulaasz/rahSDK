#pragma once

#include "Buffer.h"
#include <vector>
#include <rahMath.h>

namespace rah
{
	/**
	* Data cointainer of a Vertex
	*/
	struct VertexData
	{
		Vector3D pos;
		Vector2D tex;
		Vector3D norm;

		VertexData()
		{
			memset(this, 0, sizeof(VertexData));
		}

		VertexData(const VertexData& other)
		{
			memcpy(this, &other, sizeof(VertexData));
		}
	};

#define CPU_ACCESS_DEFAULT	0x00000000
#define CPU_ACCESS_READ		0x00000001
#define CPU_ACCESS_WRITE	0x00000002

#define VB_CREATE_DEFAULT	0x00000004	
#define VB_CREATE_STATIC	0x00000008	
#define VB_CREATE_DYNAMIC	0x00000010	

	/**
	* Create and manage a vertex buffer
	*/
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		/**
		* Creates a graphic vertex buffer using Directx11.
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _creationFlags
		* Set of flags for the creation of the buffer
		*
		*/
		void create(unsigned int _creationFlags = VB_CREATE_DEFAULT | CPU_ACCESS_DEFAULT);

		/**
		* Adds a vertex to the vertex vector
		*
		* @param _index
		* the vertex itself
		*
		*/
		void addVertex(VertexData _vertex);

		/**
		* Returns the size of the vertex buffer
		*
		* @return
		* The size of the vertex vector
		*
		*/
		size_t getVertexSize() { return m_vertexInfo.size(); }

	private:
		std::vector<VertexData> m_vertexInfo;
	};
}
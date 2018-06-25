#pragma once

#include "Buffer.h"
#include <vector>

namespace rah
{

#define CPU_ACCESS_DEFAULT	0x00000000
#define CPU_ACCESS_READ		0x00000001
#define CPU_ACCESS_WRITE	0x00000002

#define IB_CREATE_DEFAULT	0x00000004	
#define IB_CREATE_STATIC	0x00000008	
#define IB_CREATE_DYNAMIC	0x00000010	

	/**
	* Create and manage an index buffer
	*/
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		/**
		* Creates a graphic index buffer using Directx11.
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _creationFlags
		* Set of flags for the creation of the buffer
		*
		*/
		void create(unsigned int _creationFlags = IB_CREATE_DEFAULT | CPU_ACCESS_DEFAULT);

		/**
		* Adds an index to the index array
		*
		* @param _index
		* the index itself
		*
		*/
		void addIndex(unsigned int _index);

		/**
		* Returns the size of the index buffer
		*
		* @return
		* The size of the index vector
		*
		*/
		size_t getIndexSize() { return m_indexArray.size(); }

	private:
		std::vector<unsigned int> m_indexArray;
	};
}
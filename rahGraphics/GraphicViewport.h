#pragma once
#include <rahTools.h>

namespace rah
{
	/**
	* A container for a graphic viewport object
	*/
	class GraphicViewport
	{
	public:
		GraphicViewport();
		~GraphicViewport();

		/**
		* Get a pointer to the object
		*
		* @return m_viewport
		* The graphic object
		*
		*/
		void* getPtr() const
		{
			return m_viewport;
		}

		/**
		* Get a reference to the object
		*
		* @return m_viewport
		* The graphic object
		*
		*/
		void** getReference()
		{
			return &m_viewport;
		}

		/**
		* Release the pointer memory
		*
		*/
		void Release()
		{
			RAH_SAFE_DELETE(m_viewport);
		}

		/**
		* Set a reference to the object
		*
		* @param _data
		* The new data
		*
		*/
		void Set(void* _data);

	private:
		void* m_viewport;
	};
}
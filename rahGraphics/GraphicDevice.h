#pragma once

namespace rah
{
	/**
	* A container for a graphic device object
	*/
	class GraphicDevice
	{
	public:
		GraphicDevice();
		~GraphicDevice();

		/**
		* Get a pointer to the object
		*
		* @return m_device
		* The graphic object
		*
		*/
		void* getPtr() const
		{
			return m_device;
		}

		/**
		* Get a reference to the object
		*
		* @return m_device
		* The graphic object
		*
		*/
		void** getReference()
		{
			return &m_device;
		}

		/**
		* Release the pointer memory
		*
		*/
		void Release()
		{
			if (m_device)
			{
				m_device = nullptr;
			}
		}

	private:
		void* m_device;
	};
}
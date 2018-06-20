#pragma once

namespace rah
{
	/**
	* A container for a graphic device context object
	*/
	class GraphicDeviceContext
	{
	public:
		GraphicDeviceContext();
		~GraphicDeviceContext();

		/**
		* Get a pointer to the object
		*
		* @return m_deviceContext
		* The graphic object
		*
		*/
		void* getPtr() const
		{
			return m_deviceContext;
		}

		/**
		* Get a reference to the object
		*
		* @return m_deviceContext
		* The graphic object
		*
		*/
		void** getReference()
		{
			return &m_deviceContext;
		}

		/**
		* Release the pointer memory
		*
		*/
		void Release()
		{
			if (m_deviceContext)
			{
				m_deviceContext = nullptr;
			}
		}

	private:
		void* m_deviceContext;
	};
}
#pragma once

namespace rah
{
	/**
	* A container for a graphic swap chain object
	*/
	class GraphicSwapChain
	{
	public:
		GraphicSwapChain();
		~GraphicSwapChain();

		/**
		* Get a pointer to the object
		*
		* @return m_swapChain
		* The graphic object
		*
		*/
		void* getPtr() const
		{
			return m_swapChain;
		}

		/**
		* Get a reference to the object
		*
		* @return m_swapChain
		* The graphic object
		*
		*/
		void** getReference()
		{
			return &m_swapChain;
		}

		/**
		* Release the pointer memory
		*
		*/
		void Release()
		{
			if (m_swapChain)
			{
				m_swapChain = nullptr;
			}
		}

	private:
		void* m_swapChain;
	};
}
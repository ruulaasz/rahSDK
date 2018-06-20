#pragma once

namespace rah
{
	/**
	* A container for a graphic depth stencil view object
	*/
	class GraphicDepthStencilView
	{
	public:
		GraphicDepthStencilView();
		~GraphicDepthStencilView();

		/**
		* Get a pointer to the object
		*
		* @return m_depthStencilView
		* The graphic object
		*
		*/
		void* getPtr() const
		{
			return m_depthStencilView;
		}

		/**
		* Get a reference to the object
		*
		* @return m_depthStencilView
		* The graphic object
		*
		*/
		void** getReference()
		{
			return &m_depthStencilView;
		}

		/**
		* Release the pointer memory
		*
		*/
		void Release()
		{
			if (m_depthStencilView)
			{
				m_depthStencilView = nullptr;
			}
		}

	private:
		void* m_depthStencilView;
	};
}
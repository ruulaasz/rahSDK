#pragma once

namespace rah
{
	/**
	* A container for a graphic sampler state object
	*/
	class GraphicSamplerState
	{
	public:
		GraphicSamplerState();
		~GraphicSamplerState();

		/**
		* Get a pointer to the object
		*
		* @return m_samplerState
		* The graphic object
		*
		*/
		void* getPtr() const
		{
			return m_samplerState;
		}

		/**
		* Get a reference to the object
		*
		* @return m_samplerState
		* The graphic object
		*
		*/
		void** getReference()
		{
			return &m_samplerState;
		}

		/**
		* Release the pointer memory
		*
		*/
		void Release()
		{
			if (m_samplerState)
			{
				m_samplerState = nullptr;
			}
		}

	private:
		void* m_samplerState;
	};
}
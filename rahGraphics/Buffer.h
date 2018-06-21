#pragma once
#include <d3d11.h>

class GraphicDevice;

namespace rah
{
	/**
	* Base class for a graphic buffer.
	*/
	class Buffer
	{
	public:
		Buffer();
		virtual ~Buffer();

		/**
		* Creates a graphic data buffer using Directx11.
		*
		* @param _device
		* Reference to a graphic device
		*
		* @param _desc
		* The description of the buffer
		*
		* @param _initData
		* The initial data to fill the buffer
		*
		*/
		void create(GraphicDevice* _device, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _initData = nullptr);

		ID3D11Buffer* m_buffer;
	};
}
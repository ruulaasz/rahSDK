#pragma once
#include "Buffer.h"

namespace rah
{
	/**
	* A container for a constant buffer
	*/
	class ConstantBuffer :	public Buffer
	{
	public:
		ConstantBuffer();
		~ConstantBuffer();
	};
}
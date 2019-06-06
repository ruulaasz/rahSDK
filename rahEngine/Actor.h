#pragma once
#include "rahAll.h"
namespace rah
{
	class Actor
	{
	public:
		static int m_autoID;
		int m_id;
		Transform m_transform;
	public:
		virtual RahResult Initialize(void* _initData = NULL) = 0;
		virtual void Update(float _deltaTime) = 0;
		virtual void Render() = 0;
		virtual void Destroy() = 0;
		Actor();
		virtual ~Actor();
	};
}

#include "DeferredManager.h"

namespace rah
{
	DeferredManager::DeferredManager()
	{

	}

	DeferredManager::~DeferredManager()
	{

	}

	void DeferredManager::Release()
	{

	}

	RahResult DeferredManager::Initialize(void * _init)
	{
		return RahResult();
	}

	void DeferredManager::setRenderTargets()
	{
		m_renderTarget[0] = GraphicManager::GetInstance().m_renderTarget;
		m_renderTexture[0] = GraphicManager::GetInstance().m_backBuffer;

		for (size_t i = 1; i < 8; ++i)
		{
			m_renderTexture[i].CreateAsRenderTarget(GraphicManager::GetInstance().m_width, GraphicManager::GetInstance().m_height);
			GraphicManager::GetInstance().createRenderTargetView(&m_renderTarget[i], &m_renderTexture[i]);
		}

		ID3D11DeviceContext* pDeviceContext;
		pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(rah::GraphicManager::GetInstance().m_deviceContext.getPtr());

		for (size_t i = 0; i < 8; ++i)
		{
			pRenderTargets[i] = m_renderTarget[i].m_renderTarget;
		}

		ID3D11DepthStencilView* pDepthStencilView;
		pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(rah::GraphicManager::GetInstance().m_depthStencilView.getPtr());

		pDeviceContext->OMSetRenderTargets(8, pRenderTargets, pDepthStencilView);
	}
}
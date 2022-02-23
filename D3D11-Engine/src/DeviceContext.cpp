#include "DeviceContext.h"
#include "RendererContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext( ID3D11DeviceContext* pDeviceContext )
{
	m_pDeviceContext = pDeviceContext;
}

void DeviceContext::Terminate()
{
	SAFE_RELEASE( m_pDeviceContext );

	delete this;
}

bool DeviceContext::CleatRenderTargetColor( SwapChain* pSwapChain, float R, float G, float B, float A )
{
	FLOAT ClearColor[ 4 ] =
	{
		R,
		G,
		B,
		A
	};

	// Clear back buffer
	m_pDeviceContext->ClearRenderTargetView( pSwapChain->m_pRTV, ClearColor );

	return true;
}
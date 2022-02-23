#include "RendererContext.h"

#include <vector>

void RendererContext::Init()
{
	// Create D3D11 Device

	std::vector< D3D_DRIVER_TYPE > DriverTypes;

	// Use best driver type so D3D_DRIVER_TYPE_HARDWARE, and D3D_DRIVER_TYPE_HARDWARE means that all code should run on GPU.
	DriverTypes.push_back( D3D_DRIVER_TYPE_HARDWARE );
	DriverTypes.push_back( D3D_DRIVER_TYPE_WARP );
	DriverTypes.push_back( D3D_DRIVER_TYPE_REFERENCE );

	std::vector< D3D_FEATURE_LEVEL > FeatureLevels;
	FeatureLevels.push_back( D3D_FEATURE_LEVEL_11_0 );
	
	for( auto& DriverType : DriverTypes )
	{
		if( SUCCEEDED( ( D3D11CreateDevice( NULL, DriverType, NULL, NULL, FeatureLevels.data(), FeatureLevels.size(), D3D11_SDK_VERSION, &m_pDevice, &m_CurrentFeatureLevel, &m_pDeviceContext ) ) ) )
			break;
	}

	// Handoff the device context to DeviceContext class and keep a ref to both.
	m_DeviceContext = new DeviceContext( m_pDeviceContext );

	// Get Factory so we can create the swap chain.

	m_pDevice->QueryInterface( __uuidof( IDXGIDevice ), ( void** )&m_pLowLevelDevice );

	// I've got no idea what the hell an IDXGIAdapter is.
	m_pLowLevelDevice->GetParent( __uuidof( IDXGIAdapter ), ( void** )&m_pAdapter );

	m_pAdapter->GetParent( __uuidof( IDXGIFactory ), ( void** )&m_pFactory );

	m_pSwapChain = CreateSwapChain();
}

void RendererContext::Terminate()
{
	SAFE_RELEASE( m_pDevice );
	SAFE_RELEASE( m_pDeviceContext );
}

void RendererContext::Render()
{
	// Tell deivce context to clear RTV, RTV is the Swapchains back buffer.
	m_DeviceContext->CleatRenderTargetColor( m_pSwapChain, 255, 0, 255, 255 );

	// Present to swap chain.
	m_pSwapChain->Present();
}

SwapChain* RendererContext::CreateSwapChain()
{
	SwapChain* pResult;

	pResult = new SwapChain( m_pFactory, m_pDevice );

	return pResult;
}

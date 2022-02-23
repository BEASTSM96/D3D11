#include "Base.h"

#include <d3d11.h>

#include "SwapChain.h"
#include "DeviceContext.h"

class RendererContext
{
	SINGLETON( RendererContext );

public:
	 RendererContext() { Init(); }
	 ~RendererContext() { Terminate(); }

public:

	void Render();

	SwapChain* CreateSwapChain();

private:

	void Init();
	void Terminate();

private:

	SwapChain* m_pSwapChain;

	ID3D11Device* m_pDevice;
	// I like to think about a IDXGIDevice as a low level device has it handles the low level calls
	IDXGIDevice* m_pLowLevelDevice;
	IDXGIAdapter* m_pAdapter;
	IDXGIFactory* m_pFactory;

	D3D_FEATURE_LEVEL m_CurrentFeatureLevel;
	ID3D11DeviceContext* m_pDeviceContext;

	DeviceContext* m_DeviceContext;

private:

	friend class SwapChain;

};

#pragma once

#include "Base.h"

#include <d3d11.h>

// I already know what a swap chain is from vulkan but in a really simple way it handles the swapping of two or more buffer, so Back Buffer and Front Buffer, the Front Buffer should always be shown on the screen/window and the back buffer gets copied into the front buffer ready for us to use again. This process repeats again and again.

class DeviceContext;

class SwapChain
{
public:
	 SwapChain()                                                 {}
	 SwapChain( IDXGIFactory* pFactory, ID3D11Device* pDevice )  { Init( pFactory, pDevice );      }
	~SwapChain()                                                 { Terminate(); }

	void Present();

private:

	void Init( IDXGIFactory* pFactory, ID3D11Device* pDevice );
	void Terminate();

	IDXGISwapChain* m_pSwapChain;
	// Back buffer.
	ID3D11RenderTargetView* m_pRTV;

private:

	friend DeviceContext;

};

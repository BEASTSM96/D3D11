#pragma once

#include "Base.h"

#include <d3d11.h>

class SwapChain;

class DeviceContext
{
public:
	 DeviceContext( ID3D11DeviceContext* pDeviceContext );
	 ~DeviceContext() { Terminate(); }

public:

	bool CleatRenderTargetColor( SwapChain* pSwapChain, float R, float G, float B, float A );

private:

	void Terminate();

private:

	ID3D11DeviceContext* m_pDeviceContext;

};
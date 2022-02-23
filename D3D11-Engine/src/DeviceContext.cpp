/********************************************************************************************
*                                                                                           *
*                                                                                           *
*                                                                                           *
* MIT License                                                                               *
*                                                                                           *
* Copyright (c) 2020 - 2022 BEAST                                                           *
*                                                                                           *
* Permission is hereby granted, free of charge, to any person obtaining a copy              *
* of this software and associated documentation files (the "Software"), to deal             *
* in the Software without restriction, including without limitation the rights              *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                 *
* copies of the Software, and to permit persons to whom the Software is                     *
* furnished to do so, subject to the following conditions:                                  *
*                                                                                           *
* The above copyright notice and this permission notice shall be included in all            *
* copies or substantial portions of the Software.                                           *
*                                                                                           *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                  *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE               *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                    *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,             *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE             *
* SOFTWARE.                                                                                 *
*********************************************************************************************
*/

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
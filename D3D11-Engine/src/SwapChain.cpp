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

#include "SwapChain.h"
#include "RendererContext.h"
#include "MainWindow.h"

void SwapChain::Init( IDXGIFactory* pFactory, ID3D11Device* pDevice )
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
	// Use doublebuffer.
	SwapChainDesc.BufferCount = 2;

	SwapChainDesc.BufferDesc.Width = MainWindow::Get().GetWidth();
	SwapChainDesc.BufferDesc.Height = MainWindow::Get().GetHeight();

	// Pixel Format
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = MainWindow::Get().OSWindow();
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = TRUE;

	// Create SwapChain.
	D3D_CHECK( pFactory->CreateSwapChain( pDevice, &SwapChainDesc, &m_pSwapChain ) );

	// Get back buffer texture. I think a texture in D3D11 is like one in Vulkan i.e. where a ID3D11Texture2D is just memory in the GPU
	ID3D11Texture2D* pBuffer;
	m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( void** )&pBuffer );

	// Convert texture 2D to RTV.
	// NULL here as the info is already passed.
	pDevice->CreateRenderTargetView( pBuffer, NULL, &m_pRTV );

	SAFE_RELEASE( pBuffer );
}

void SwapChain::Terminate()
{
	SAFE_RELEASE( m_pSwapChain );

	delete this;
}

void SwapChain::Present()
{
	m_pSwapChain->Present( 1, 0 );
}

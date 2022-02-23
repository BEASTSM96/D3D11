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

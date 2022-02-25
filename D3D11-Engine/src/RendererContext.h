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

#include "Base.h"

#include <d3d11.h>

#include "SwapChain.h"
#include "DeviceContext.h"

class VertexBuffer;

class RendererContext
{
	SINGLETON( RendererContext );

public:
	 RendererContext() { Init(); }
	 ~RendererContext() { Terminate(); }

public:

	void Render();

	SwapChain* CreateSwapChain();

	VertexBuffer* CreateVertexBuffer();

private:

	void Init();
	void Terminate();
	
	void CreateTriangleShader();
	void GetShaderBufferAndSize( void** ppCode, uint32_t* pSize );

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

	// TEMP
	VertexBuffer* m_pVertexBuffer;

	ID3DBlob* m_pVSBlob = nullptr;
	ID3DBlob* m_pPSBlob = nullptr;

	ID3D11VertexShader* m_VSShader;
	ID3D11PixelShader* m_PSShader;

private:

	friend class SwapChain;
	friend class VertexBuffer;

};

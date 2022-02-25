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

#include "RendererContext.h"
#include "VertexBuffer.h"
#include "MainWindow.h"

#include <d3dcompiler.h>
#include <vector>

struct Vec3
{
	//Vec3() : x( 0 ), y( 0 ), z( 0 ) {}
	//Vec3( float _x, float _y, float _z ) : x( _x ), y( _y ), z( _z ) {}

	float x, y, z;
};

struct Vertex
{
	Vec3 Position;
};

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

	// Hand off the device context to DeviceContext class and keep a ref to both.
	m_DeviceContext = new DeviceContext( m_pDeviceContext );

	// Get Factory so we can create the swap chain.

	m_pDevice->QueryInterface( __uuidof( IDXGIDevice ), ( void** )&m_pLowLevelDevice );

	// I've got no idea what the hell an IDXGIAdapter is.
	m_pLowLevelDevice->GetParent( __uuidof( IDXGIAdapter ), ( void** )&m_pAdapter );

	m_pAdapter->GetParent( __uuidof( IDXGIFactory ), ( void** )&m_pFactory );

	m_pSwapChain = CreateSwapChain();

	//////////////////////////////////////////////////////////////////////////
	// TEMP
	//////////////////////////////////////////////////////////////////////////

	CreateTriangleShader();

	//std::vector< Vertex > TraingleVertex;
	//TraingleVertex.push_back( { -0.5f, -0.5f, 0.0f } );

	Vertex TraingleVertex[] =
	{
		{ -0.5f, -0.5f, 0.0f },
		{ 0.0f, 0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f }
	};

	m_pVertexBuffer = CreateVertexBuffer();

	void* pShaderByteCode = nullptr;
	uint32_t SizeShader = 0;
	GetShaderBufferAndSize( &pShaderByteCode, &SizeShader );

	m_pVertexBuffer->Load( m_pDevice, TraingleVertex, sizeof( Vertex ), ARRAYSIZE( TraingleVertex ), pShaderByteCode, SizeShader );
}

void RendererContext::Terminate()
{
	SAFE_RELEASE( m_pDevice );
	SAFE_RELEASE( m_pDeviceContext );

	m_pVertexBuffer->Terminate();
}

void RendererContext::Render()
{
	// Tell device context to clear RTV, RTV is the Swapchains back buffer.
	m_DeviceContext->ClearRenderTargetColor( m_pSwapChain, 255, 0, 255, 255 );

	uint32_t w, h;
	w = MainWindow::Get().GetWidth();
	h = MainWindow::Get().GetHeight();

	m_DeviceContext->SetViewportSize( w, h );

	m_pDeviceContext->VSSetShader( m_VSShader, nullptr, 0 );
	m_pDeviceContext->PSSetShader( m_PSShader, nullptr, 0 );

	m_DeviceContext->SetVertexBuffer( m_pVertexBuffer );

	m_DeviceContext->DrawTriangleList( m_pVertexBuffer->GetVertexListSize(), 0 );

	// Present to swap chain.
	m_pSwapChain->Present();
}

SwapChain* RendererContext::CreateSwapChain()
{
	return new SwapChain( m_pFactory, m_pDevice );
}

VertexBuffer* RendererContext::CreateVertexBuffer()
{
	return new VertexBuffer();
}


//////////////////////////////////////////////////////////////////////////
// TEMP - Move to shader class
//////////////////////////////////////////////////////////////////////////

void RendererContext::CreateTriangleShader()
{
	ID3DBlob* pErrorBlob = nullptr;

	D3DCompileFromFile( L"assets/shader.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", NULL, NULL, &m_pVSBlob, &pErrorBlob );
	D3DCompileFromFile( L"assets/shader.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", NULL, NULL, &m_pPSBlob, &pErrorBlob );

	m_pDevice->CreateVertexShader( m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), nullptr, &m_VSShader );
	m_pDevice->CreatePixelShader( m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize(), nullptr, &m_PSShader );
}

void RendererContext::GetShaderBufferAndSize( void** ppCode, uint32_t* pSize )
{
	*ppCode = m_pVSBlob->GetBufferPointer();
	*pSize = m_pVSBlob->GetBufferSize();
}

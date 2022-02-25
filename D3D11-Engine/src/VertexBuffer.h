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

#include <d3d11.h>

#include <Windows.h>
#include <stdint.h>
#include <vector>

class DeviceContext;

class VertexBuffer
{
public:
	 VertexBuffer() {}
	~VertexBuffer();

public:

	void Load( ID3D11Device* pDevice, void* pListVertices, uint32_t SizeVertex, uint32_t SizeList, void* ShaderByteCode, uint32_t SizeOfShader );
	void Terminate();

	uint32_t GetVertexListSize() { return m_SizeList; }

private:

	uint32_t m_SizeVertex = 0;
	uint32_t m_SizeList = 0;

	ID3D11Buffer* m_pBuffer = nullptr;
	ID3D11InputLayout* m_pLayout = nullptr;

private:

	friend class DeviceContext;

};
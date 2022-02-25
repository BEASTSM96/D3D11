#include "VertexBuffer.h"

#include "RendererContext.h"

VertexBuffer::~VertexBuffer()
{

}

void VertexBuffer::Load( ID3D11Device* pDevice, void* pListVertices, uint32_t SizeVertex, uint32_t SizeList, void* ShaderByteCode, uint32_t SizeOfShader )
{
	SAFE_RELEASE( m_pLayout );
	SAFE_RELEASE( m_pBuffer );

	D3D11_BUFFER_DESC BufferDesc = {};
	// GPU, Read and Write.
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	// Size in bytes.
	BufferDesc.ByteWidth = SizeVertex * SizeList;
	// Bind as a vertex buffer.
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA SubResData = {};
	SubResData.pSysMem = pListVertices;

	m_SizeVertex = SizeVertex;
	m_SizeList = SizeList;

	D3D_CHECK( pDevice->CreateBuffer( &BufferDesc, &SubResData, &m_pBuffer ) );

	// NAME - INDEX - FORMAT - SLOT - BYTE OFFSET - SLOT CLASS - DATA STEP RATE
	std::vector<D3D11_INPUT_ELEMENT_DESC> Layouts;
	Layouts.push_back( { "POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 } );

	D3D_CHECK( pDevice->CreateInputLayout( Layouts.data(), Layouts.size(), ShaderByteCode, SizeOfShader, &m_pLayout ) );
}

void VertexBuffer::Terminate()
{
	SAFE_RELEASE( m_pLayout );
	SAFE_RELEASE( m_pBuffer );

	delete this;
}

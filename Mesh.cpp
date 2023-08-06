#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	if (m_vertexBuffer) { m_vertexBuffer->Release(); m_vertexBuffer = NULL; }
	if (m_indexBuffer) { m_indexBuffer->Release(); m_indexBuffer = NULL; }
}

void Mesh::Initialize(ID3D11Device* _device)
{
	CreateVertexBuffer(_device);
	CreateIndexBuffer(_device);
}

void Mesh::Render()
{
}

void Mesh::CreateVertexBuffer(ID3D11Device* _device)
{
	// Create a vertex buffer
	{
		vertices =
		{
			{ { -1.0f,  1.0f, 0.0f, 1.0f }, { 0.f, 0.f },},
			{ {  0.5f,  1.0f, 0.0f, 1.0f }, { 1.f, 0.f },},
			{ { -1.0f, -1.0f, 0.0f, 1.0f }, { 0.f, 1.f },},
			{ {  0.5f, -1.0f, 0.0f, 1.0f }, { 1.f, 1.f },},
		};

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bufferDesc.ByteWidth = UINT(sizeof(Vertex) * vertices.size());             // size is the VERTEX struct * 3
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer
		bufferDesc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0, };
		vertexBufferData.pSysMem = vertices.data();
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		const HRESULT hr = _device->CreateBuffer(&bufferDesc, &vertexBufferData, &m_vertexBuffer);
		if (FAILED(hr)) {
			std::cout << "CreateBuffer() failed. " << std::hex << hr << std::endl;
		};
	}
}

void Mesh::CreateIndexBuffer(ID3D11Device* _device)
{
	// Create an index buffer
	{
		indices =
		{
			 0, 1 ,2,
			 2, 1, 3
		};

		m_indexCount = UINT(indices.size());

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bufferDesc.ByteWidth = UINT(sizeof(uint16_t) * indices.size());
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;       // use as a vertex buffer
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer
		bufferDesc.StructureByteStride = sizeof(uint16_t);

		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indices.data();
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;

		_device->CreateBuffer(&bufferDesc, &indexBufferData, &m_indexBuffer);
	}
}

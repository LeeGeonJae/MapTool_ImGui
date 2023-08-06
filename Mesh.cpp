#include "Mesh.h"

void Mesh::Initialize(const vector<Vertex>& vertexBuffer, const vector<uint16_t>& indexbuffer)
{
	CreateVertexBuffer(vertexBuffer);
	CreateIndexBuffer(indexbuffer);
}

void Mesh::Render()
{
}

void Mesh::CreateVertexBuffer(const vector<Vertex>& buffer)
{

}

void Mesh::CreateIndexBuffer(const vector<uint16_t>& buffer)
{

}

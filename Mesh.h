#pragma once
#include "defalut.h"

class Texture;

class Mesh
{
public:
	Mesh();
	~Mesh();

public:
	void Initialize(ID3D11Device* _device);
	void Render();

public:
	void SetTexture(Texture* tex) { m_texture = tex; }

	ID3D11Buffer* const* GetVertexBuffer() { return &m_vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return m_indexBuffer; }
	UINT GetIndexCount() { return m_indexCount; }
	Texture* GetTexture() { return m_texture; }

private:
	void CreateVertexBuffer(ID3D11Device* _device);
	void CreateIndexBuffer(ID3D11Device* _device);

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	UINT m_indexCount;

	Texture* m_texture = {};

	vector<uint16_t> indices = {};
	vector<Vertex> vertices = {};
};
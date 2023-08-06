#pragma once
#include "defalut.h"

class Texture;

class Mesh
{
public:
	void Initialize(const vector<Vertex>& vertexBuffer, const vector<uint16_t>& indexbuffer);
	void Render();

	void SetTransform(const Transform& t) { _transform = t; }
	void SetTexture(shared_ptr<Texture> tex) { _tex = tex; }

private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBuffer(const vector<uint16_t>& buffer);

private:
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	Transform _transform = {};
	shared_ptr<Texture> _tex = {};

};
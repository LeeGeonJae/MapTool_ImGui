#pragma once
#include "defalut.h"

class Example
{
public:
	Example(HWND window, int width, int height, int canvasWidth, int canvasHeight)
	{
		Initialize(window, width, height, canvasWidth, canvasHeight);
	}

	// https://docs.microsoft.com/en-us/windows/win32/direct3d11/how-to--compile-a-shader
	void InitShaders();
	void Initialize(HWND window, int width, int height, int canvasWidth, int canvasHeight);

	void Update();
	void Render();
	void Clean();

public:
	// 이름 짓기 규칙
	// https://github.com/Microsoft/DirectXTK/wiki/Implementation#naming-conventions
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	D3D11_VIEWPORT viewport;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Texture2D* canvasTexture = nullptr;
	ID3D11ShaderResourceView* canvasTextureView = nullptr;
	ID3D11RenderTargetView* canvasRenderTargetView = nullptr;
	ID3D11SamplerState* colorSampler;
	UINT indexCount;	

	int canvasWidth, canvasHeight;
	float backgroundColor[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
};
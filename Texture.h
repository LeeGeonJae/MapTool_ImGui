#pragma once
#include "defalut.h"

class Texture
{
public:
	Texture();
	~Texture();

public:
	void Initialize(ID3D11Device* _device, int _canvasWidth, int _canvasHeight, const wstring& path);

private:
	void CreateTexture(ID3D11Device* _device, const wstring& path);

private:
	ID3D11Texture2D* m_canvasTexture = nullptr;
	ID3D11SamplerState* m_colorSampler = nullptr;
	ID3D11ShaderResourceView* m_canvasTextureView = nullptr;
	ID3D11RenderTargetView* m_canvasRenderTargetView = nullptr;
	int m_canvasWidth;
	int m_canvasHeight;
};


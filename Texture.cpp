#include "Texture.h"


Texture::Texture()
	: m_canvasWidth(0)
	, m_canvasHeight(0)
{
}

Texture::~Texture()
{
}

void Texture::Initialize(ID3D11Device* _device, int _canvasWidth, int _canvasHeight, const wstring& path)
{
	m_canvasWidth = _canvasWidth;
	m_canvasHeight = _canvasHeight;

	CreateTexture(_device, path);
}

void Texture::CreateTexture(ID3D11Device* _device, const wstring& path)
{
	// �ؽ�ó ������ ���� ���÷� ����(Sampler State) ����
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;		// �ؽ�ó ���͸� ��� ���� (�ּ�/�ִ�/�߰��� ���͸�)
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;		// U �� �ؽ�ó �ּ� ��� ����
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;		// V �� �ؽ�ó �ּ� ��� ����
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;		// W �� �ؽ�ó �ּ� ��� ����
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;		// ���ð� ���� �� ����� �Լ� ����
	sampDesc.MinLOD = 0;									// �ؽ�ó�� �ּ� LOD (���� ���� ������) ����
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;					// �ؽ�ó�� �ִ� LOD ����

	// ���÷� ���� ����
	_device->CreateSamplerState(&sampDesc, &m_colorSampler);

	// �ؽ�ó ������ ���� ����
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.MipLevels = textureDesc.ArraySize = 1;		// MIP �� ������ �迭 ũ�� ����
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	// �ؽ�ó ���� ���� (32��Ʈ RGBA �ε� �Ҽ���)
	textureDesc.SampleDesc.Count = 1;						// ��Ƽ ���ø� ����
	textureDesc.Usage = D3D11_USAGE_DYNAMIC;				// �ؽ�ó�� ��� ��� ���� (�������� ������Ʈ ����)
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;		// �ؽ�ó�� ���̴� ���ҽ��� ���ε�
	textureDesc.MiscFlags = 0;								// ��Ÿ Ư�� �ɼ� ����
	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU ������ ���� ���� (�ؽ�ó ���� ����)
	textureDesc.Width = m_canvasWidth;						// �ؽ�ó�� ���� ũ�� ����
	textureDesc.Height = m_canvasHeight;					// �ؽ�ó�� ���� ũ�� ����

	// �ؽ�ó ����
	_device->CreateTexture2D(&textureDesc, nullptr, &m_canvasTexture);

	// �ؽ�ó�� ���������� �����Ǿ��ٸ�, ���̴� ���ҽ� ��� ���� Ÿ�� �並 �����Ѵ�.
	if (m_canvasTexture)
	{
		// �ؽ�ó�� ���� ���̴� ���ҽ� �� ����
		_device->CreateShaderResourceView(m_canvasTexture, nullptr, &m_canvasTextureView);

		// �ؽ�ó�� ���� ���� Ÿ�� �� ����
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		renderTargetViewDesc.Format = textureDesc.Format;					// ���� Ÿ�� ���� ���� ���� (�ؽ�ó ���İ� �����ϰ�)
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D �ؽ�ó�� ����
		renderTargetViewDesc.Texture2D.MipSlice = 0;						// MIP �� ���� ���� (0�� �⺻ ����)

		_device->CreateRenderTargetView(m_canvasTexture, &renderTargetViewDesc, &m_canvasRenderTargetView);
	}
	else
	{
		std::cout << "CreateRenderTargetView() error" << std::endl;
	}

	// Create Textrue File
	{
		DirectX::TexMetadata md;
		DirectX::ScratchImage img;
		HRESULT hr = DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, &md, img);
		assert(SUCCEEDED(hr));

		hr = DirectX::CreateShaderResourceView(_device, img.GetImages(), img.GetImageCount(), md, &m_canvasTextureView);
		assert(SUCCEEDED(hr));
	}
}

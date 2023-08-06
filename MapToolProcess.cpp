#include "MapToolProcess.h"
#include "Mesh.h"
#include "Texture.h"
#include "Example.h"

MapToolProcess::MapToolProcess()
	: m_Mesh()
	, m_Texture(nullptr)
	, m_Example(nullptr)
	, m_hwnd(nullptr)
{
}

MapToolProcess::~MapToolProcess()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	m_Example->Clean();
	DestroyWindow(m_hwnd);

	for (auto mesh : m_Mesh)
		delete mesh;

	delete m_Texture;
}

void MapToolProcess::Initialize(HWND _hwnd)
{
	m_hwnd = _hwnd;

	m_Example = new Example(_hwnd);
	m_Texture = new Texture;

	Mesh* mesh1 = new Mesh;
	mesh1->SetXYPosition(2, 1);
	mesh1->Initialize(m_Example->device);
	mesh1->SetTexture(m_Texture);
	Mesh* mesh2 = new Mesh;
	mesh2->SetXYPosition(5, 5);
	mesh2->Initialize(m_Example->device);
	mesh2->SetTexture(m_Texture);

	m_Mesh.push_back(mesh1);
	m_Mesh.push_back(mesh2);

	m_Texture->Initialize(m_Example->device, L"Golem.png");

	// ImGui 생성
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.DisplaySize = ImVec2(WIDTH, HEIGHT);
	ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplDX11_Init(m_Example->device, m_Example->deviceContext);
	ImGui_ImplWin32_Init(_hwnd);
}

void MapToolProcess::Loop()
{
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Start the Dear ImGui frame
			ImGui_ImplDX11_NewFrame();//TODO: IMGUI 사용
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Background Color");

			// ImGui렌더러
			ImGuiRender();

			//ImGui::SliderFloat3("RGB(0.0->1.0)", canvasColor, 0.0f, 1.0f);

			ImGui::End();
			ImGui::Render();

			// 게임 엔진 업데이트 및 렌더러
			Update();
			Render();

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());//TODO: IMGUI 사용

			// switch the back buffer and the front buffer
			m_Example->swapChain->Present(1, 0);
		}
	}
}

void MapToolProcess::Update()
{
	m_Example->Update(m_Mesh[0]);
}

void MapToolProcess::Render()
{
	m_Example->RenderBegin();

	for(auto mesh : m_Mesh)
		m_Example->MeshRender(mesh);
}

void MapToolProcess::ImGuiRender()
{
	// ImGui 렌더러
	if (ImGui::Button("X++"))
	{
		m_Mesh[1]->AddXYPosition(1, 0);
		m_Mesh[1]->Initialize(m_Example->device);
	}
	if (ImGui::Button("Y++"))
	{
		m_Mesh[1]->AddXYPosition(0, 1);
		m_Mesh[1]->Initialize(m_Example->device);
	}
}
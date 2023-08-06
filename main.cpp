#include "Example.h"
#include "Mesh.h"
#include "Texture.h"
#include "MapToolProcess.h"

HWND g_hwnd;

void Init();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// �ܼ�â�� ������ ����뿡 �����մϴ�.
int main()
{
	// ������ ����
	Init();

	// ���� ���μ���
	MapToolProcess process;
	process.Initialize(g_hwnd);
	process.Loop();

	//UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}


void Init()
{
	WNDCLASSEX wc = {
	sizeof(WNDCLASSEX),
	CS_CLASSDC,
	WndProc,
	0L,
	0L,
	GetModuleHandle(NULL),
	NULL,
	NULL,
	NULL,
	NULL,
	L"HongLabGraphics", // lpszClassName, L-string
	NULL
	};

	RegisterClassEx(&wc);

	// ������ �׷����� �ػ󵵸� �����ϱ� ����
	RECT wr = { 0, 0, WIDTH, HEIGHT };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		L"HongLabGraphics Example",
		WS_OVERLAPPEDWINDOW,
		100, // ������ ���� ����� x ��ǥ
		100, // ������ ���� ����� y ��ǥ
		wr.right - wr.left, // ������ ���� ���� �ػ�
		wr.bottom - wr.top, // ������ ���� ���� �ػ�
		NULL,
		NULL,
		wc.hInstance,
		NULL);

	g_hwnd = hwnd;

	ShowWindow(g_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hwnd);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Windows procedure
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		// Reset and resize swapchain
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu 
			return 0;
		break;
	case WM_MOUSEMOVE:
		//std::cout << "Mouse " << LOWORD(lParam) << " " << HIWORD(lParam) << std::endl;
		break;
	case WM_LBUTTONUP:
		//std::cout << "WM_LBUTTONUP Left mouse button" << std::endl;
		break;
	case WM_RBUTTONUP:
		//std::cout << "WM_RBUTTONUP Right mouse button" << std::endl;
		break;
	case WM_KEYDOWN:
		//std::cout << "WM_KEYDOWN " << (int)wParam << std::endl;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

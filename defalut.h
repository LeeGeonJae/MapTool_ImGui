#pragma once

#include <windows.h>
#include <memory>
#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include <filesystem>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

using namespace std;

const int WIDTH = 1500;
const int HEIGHT = 900;
const int CANVAS_WIDTH = WIDTH / 80;
const int CANVAS_HEIGHT = HEIGHT / 80;

// 수학의 4차원 벡터(vector)를 의미합니다. 
// std::vector와는 다릅니다.
struct Vec4
{
	float v[4];
};

struct Vec2
{
	float v[2];
};

struct Vertex
{
	Vec4 pos;
	Vec2 uv;
};

struct Transform
{
	Vec4 offset;
};
#pragma once

#include <windows.h>
#include <memory>
#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include <filesystem>

#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

using namespace std;

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
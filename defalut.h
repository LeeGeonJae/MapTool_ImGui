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

const int WIDTH = 1500;
const int HEIGHT = 900;
const int CANVAS_WIDTH = WIDTH / 80;
const int CANVAS_HEIGHT = HEIGHT / 80;

// ������ 4���� ����(vector)�� �ǹ��մϴ�. 
// std::vector�ʹ� �ٸ��ϴ�.
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
#pragma once
#include "defalut.h"

class Mesh;
class Texture;
class Example;

class MapToolProcess
{
public:
	MapToolProcess();
	~MapToolProcess();

public:
	void Initialize(HWND _hwnd);
	void Loop();
	void Update();
	void Render();
	void ImGuiRender();

public:
	vector<Mesh*>	m_Mesh;
	Texture*	m_Texture;
	Example*	m_Example;

	HWND m_hwnd;
};


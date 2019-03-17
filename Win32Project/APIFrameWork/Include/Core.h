#pragma once
#include "Game.h"

class CCore
{
	
DECLARE_SINGLE(CCore)

private:
	static bool m_bLoop;

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	RESOLUTION m_tRS;
	

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	ATOM MyRegisterClass();
	BOOL Create();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


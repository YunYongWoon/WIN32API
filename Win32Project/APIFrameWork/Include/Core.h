#pragma once
#include "Game.h"

class CCore
{
private:
	static bool m_bLoop;

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	RESOLUTION m_tRS;

public:
	RESOLUTION GetResolution() const {
		return m_tRS;
	}

	HWND GetWindowHandle() const {
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance() const {
		return m_hInst;
	}
	
	void DestroyGame() {
		DestroyWindow(m_hWnd);
	}

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

private:
	ATOM MyRegisterClass();
	BOOL Create();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CCore)
};


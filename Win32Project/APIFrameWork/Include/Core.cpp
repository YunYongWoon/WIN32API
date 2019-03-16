#include "Core.h"

CCore* CCore::m_pInst = NULL;
bool CCore::m_bLoop = true;

CCore::CCore() {
}


CCore::~CCore() {
}

bool CCore::Init(HINSTANCE hInst) {
	m_hInst = hInst;
	MyRegisterClass();

	// 해상도 설정
	m_tRS.iW = 1280;
	m_tRS.iH = 720;

	Create();

	return true;
}

int CCore::Run() {
	MSG msg;

	// 기본 메시지 루프입니다.
	while (m_bLoop) {
		// PeekMessage는 메시지가 메시지큐에 없어도 바로 빠져 나온다.
		// 메시지가 있을 경우 true, 없을 경우 false가 된다.
		// 메시지가 없는 시간이 윈도우의 데드타임이다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// 윈도우가 데드타임일 경우
		else {
		}
	}

	return (int)msg.wParam;
	
}

ATOM CCore::MyRegisterClass() {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CCore::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_WIN32PROJECT);		//메뉴
	wcex.lpszClassName = L"AR13API";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
	return ATOM();
}

BOOL CCore::Create() {

	m_hWnd = CreateWindowW(L"AR13API", L"AR13API", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd) {
		return FALSE;
	}

	// 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를
	// 구해준다.

	RECT rc = { 0,0,m_tRS.iW,m_tRS.iH };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);


	// 위에서 구해준 크기로 윈도우 클라이언트 영역의 크기를 
	// 원하는 크기로 맞춰줘야 한다.
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100,
		rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	return 0;
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return LRESULT();
}


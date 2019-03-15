// GetMessage.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GetMessage.h"

typedef struct _tagRectangle {
	float l, t, r, b;
}RECTANGLE, *PRECTANGLE;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
HDC g_hDC;
bool g_bLoop = true;
RECTANGLE g_tPlayerRC = { 100,100,200,200 };

// 시간을 구하기 위한 변수들
LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float g_fDeltatime;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Run();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GETMESSAGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	g_hDC = GetDC(g_hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GETMESSAGE));

    MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);
    // 기본 메시지 루프입니다.
    while (g_bLoop)
    {
	// PeekMessage는 메시지가 메시지큐에 없어도 바로 빠져 나온다.
	// 메시지가 있을 경우 true, 없을 경우 false가 된다.
	// 메시지가 없는 시간이 윈도우의 데드타임이다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	// 윈도우가 데드타임일 경우
		else {
				Run();
					
		}
    }

	ReleaseDC(g_hWnd, g_hDC);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GETMESSAGE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_GETMESSAGE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   // 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를
   // 구해준다.

   RECT rc = { 0,0,800,600 };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);


   // 위에서 구해준 크기로 윈도우 클라이언트 영역의 크기를 
   // 원하는 크기로 맞춰줘야 한다.
   SetWindowPos(hWnd, HWND_TOPMOST, 100, 100,
	   rc.right - rc.left, rc.bottom - rc.top,SWP_NOMOVE | SWP_NOZORDER);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY: // Window 종룔될 때 들어오는 메시지.
		g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Run() {
	// DeltaTime을 구해준다.
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);

	g_fDeltatime = (tTime.QuadPart - g_tTime.QuadPart) / (float)g_tSecond.QuadPart;
	g_tTime = tTime;

	static float fTimeScale = 1.f;

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		fTimeScale -= g_fDeltatime;

		if (fTimeScale < 0.f)
			fTimeScale = 0.f;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000) {
		fTimeScale += g_fDeltatime;

		if (fTimeScale > 1.f)
			fTimeScale = 1.f;
	}

	if (GetAsyncKeyState(VK_F3) & 0x8000) {
		fTimeScale = 0;
	}

	// 플레이어 초당 이동속도 500
	float fSpeed = 500 * g_fDeltatime*fTimeScale;

	if (GetAsyncKeyState('D') & 0x8000) {
		g_tPlayerRC.l += fSpeed;
		g_tPlayerRC.r += fSpeed;
	}

	if (GetAsyncKeyState('A') & 0x8000) {
		g_tPlayerRC.l -= fSpeed;
		g_tPlayerRC.r -= fSpeed;
	}

	if (GetAsyncKeyState('W') & 0x8000) {
		g_tPlayerRC.t -=fSpeed;
		g_tPlayerRC.b -=fSpeed;
	}

	if (GetAsyncKeyState('S') & 0x8000) {
		g_tPlayerRC.t += fSpeed;
		g_tPlayerRC.b += fSpeed;
	}

	RECT rcWindow;
	GetClientRect(g_hWnd, &rcWindow);

	if (g_tPlayerRC.l < 0) {
		g_tPlayerRC.l = 0;
		g_tPlayerRC.r = 100;
	}

	else if (g_tPlayerRC.r > rcWindow.right) {
		g_tPlayerRC.r = rcWindow.right;
		g_tPlayerRC.l = rcWindow.right - 100;
	}

	if (g_tPlayerRC.t < 0) {
		g_tPlayerRC.t = 0;
		g_tPlayerRC.b = 100;
	}

	else if (g_tPlayerRC.b > rcWindow.bottom) {
		g_tPlayerRC.b = rcWindow.bottom;
		g_tPlayerRC.t = rcWindow.bottom - 100;
	}


	Rectangle(g_hDC, g_tPlayerRC.l, g_tPlayerRC.t, g_tPlayerRC.r, g_tPlayerRC.b);
}

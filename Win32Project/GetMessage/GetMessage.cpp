// GetMessage.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GetMessage.h"
#include "list"
#include <math.h>

#define PI  3.14159f

using namespace std;

typedef struct _tagRectangle {
	float l, t, r, b;
}RECTANGLE, *PRECTANGLE;

typedef struct _tagSphere {
	float x;
	float y;
	float r;
}SPHERE, *PSPHERE;

typedef struct _tagMonster {
	SPHERE tSphere;
	float fSpeed;
	float fTime;
	float fLimitTime;
	int iDir;
}MONSTER, *PMONSTER;

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND g_hWnd;
HDC g_hDC;
bool g_bLoop = true;
SPHERE g_tPlayer = { 50.f,50.f,50.f };
POINT g_tGunPos;
float g_fGunLength = 70.f;
float g_fPlayerAngle;
MONSTER g_tMonster;

// �÷��̾� �Ѿ�
typedef struct _tagBullet {
	SPHERE tSphere;
	float fDist;
	float fLimitDist;
	float fAngle;
}BULLET,*PBULLET;

// �÷��̾� �Ѿ�
list<BULLET> g_PlayerBulletList;
// ���� �Ѿ�
list<BULLET> g_MonsterBulletList;

// �ð��� ���ϱ� ���� ������
LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float g_fDeltatime;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GETMESSAGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	// ȭ��� DC ����
	g_hDC = GetDC(g_hWnd);

	// ���� �ʱ�ȭ
	g_tMonster.tSphere.x = 800.f - 50.f;
	g_tMonster.tSphere.y = 50.f;
	g_tMonster.tSphere.r = 50.f;
	g_tMonster.fSpeed = 300.f;
	g_tMonster.fTime = 0.f;
	g_tMonster.fLimitTime = 0.5f;
	g_tMonster.iDir = 1;

	// �÷��̾� �ѱ��� ��ġ�� �����ش�.
	g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
	g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GETMESSAGE));

    MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);
    // �⺻ �޽��� �����Դϴ�.
    while (g_bLoop)
    {
	// PeekMessage�� �޽����� �޽���ť�� ��� �ٷ� ���� ���´�.
	// �޽����� ���� ��� true, ���� ��� false�� �ȴ�.
	// �޽����� ���� �ð��� �������� ����Ÿ���̴�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	// �����찡 ����Ÿ���� ���
		else {
				Run();				
		}
    }

	ReleaseDC(g_hWnd, g_hDC);

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   // ���� ������ Ÿ��Ʋ�ٳ� �޴��� ������ �������� ũ�⸦
   // �����ش�.

   RECT rc = { 0,0,800,600 };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);


   // ������ ������ ũ��� ������ Ŭ���̾�Ʈ ������ ũ�⸦ 
   // ���ϴ� ũ��� ������� �Ѵ�.
   SetWindowPos(hWnd, HWND_TOPMOST, 100, 100,
	   rc.right - rc.left, rc.bottom - rc.top,SWP_NOMOVE | SWP_NOZORDER);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
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
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY: // Window ����� �� ������ �޽���.
		g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
	// DeltaTime�� �����ش�.
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

	// �÷��̾� �ʴ� �̵��ӵ� 500
	float fSpeed = 400.f * g_fDeltatime*fTimeScale;

	// �÷��̾��� �̵�

	if (GetAsyncKeyState('A') & 0x8000) {
		g_fPlayerAngle -= PI * g_fDeltatime * fTimeScale;
	}

	if (GetAsyncKeyState('D') & 0x8000) {
		g_fPlayerAngle += PI * g_fDeltatime * fTimeScale;
	}

	if (GetAsyncKeyState('S') & 0x8000) {
		g_tPlayer.x -= fSpeed * cosf(g_fPlayerAngle) * fTimeScale;
		g_tPlayer.y -= fSpeed * sinf(g_fPlayerAngle) * fTimeScale;
	}

	if (GetAsyncKeyState('W') & 0x8000) {

		g_tPlayer.x += fSpeed * cosf(g_fPlayerAngle) * fTimeScale;
		g_tPlayer.y += fSpeed * sinf(g_fPlayerAngle) * fTimeScale;;
	}

	// �ѱ� ��ġ�� ���Ѵ�.
	g_tGunPos.x = g_tPlayer.x + cosf(g_fPlayerAngle) * g_fGunLength;
	g_tGunPos.y = g_tPlayer.y + sinf(g_fPlayerAngle) * g_fGunLength;

	// �Ѿ� ����
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		BULLET tBullet;
		tBullet.tSphere.x = g_tGunPos.x + cosf(g_fPlayerAngle) * 25.f;
		tBullet.tSphere.y = g_tGunPos.y + sinf(g_fPlayerAngle) * 25.f;
		tBullet.tSphere.r = 5.f;
		 
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 500.f;
		tBullet.fAngle = g_fPlayerAngle;
	
		g_PlayerBulletList.push_back(tBullet);
	}

	if (GetAsyncKeyState('1') & 0x8000) {
		float fAngle = g_fPlayerAngle - PI / 12.f;
		for (int i = 0; i < 3; i++) {
			BULLET tBullet;
			tBullet.tSphere.x = g_tGunPos.x + cosf(fAngle) * 25.f;
			tBullet.tSphere.y = g_tGunPos.y + sinf(fAngle) * 25.f;
			tBullet.tSphere.r = 5.f;

			tBullet.fDist = 0.f;
			tBullet.fLimitDist = 500.f;
			tBullet.fAngle = fAngle;

			g_PlayerBulletList.push_back(tBullet);

			fAngle += PI / 12.f;
		}
	}

	if (GetAsyncKeyState('2') & 0x8000) {
		float fAngle = g_fPlayerAngle - 2 * PI / 36.f;
		for (int i = 0; i < 36; i++) {
			BULLET tBullet;
			tBullet.tSphere.x = g_tGunPos.x + cosf(fAngle) * 25.f;
			tBullet.tSphere.y = g_tGunPos.y + sinf(fAngle) * 25.f;
			tBullet.tSphere.r = 5.f;

			tBullet.fDist = 0.f;
			tBullet.fLimitDist = 500.f;
			tBullet.fAngle = fAngle;

			g_PlayerBulletList.push_back(tBullet);

			fAngle += 2 * PI / 36.f;
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		// ���콺 ��ġ�� ���´�
		POINT ptMouse;

		// ��ũ�� ��ǥ�� �������� �޾ƿ´�
		GetCursorPos(&ptMouse);
		// ��ũ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� �ٲپ��ش�.
		ScreenToClient(g_hWnd, &ptMouse);

		// �÷��̾�� �浹ó���Ѵ�.
		/*if (g_tPlayerRC.l <= ptMouse.x && g_tPlayerRC.r >= ptMouse.x && 
			g_tPlayerRC.t <= ptMouse.y && g_tPlayerRC.b >= ptMouse.y) {
			MessageBox(NULL, L"�÷��̾� Ŭ��", L"���콺Ŭ��", MB_OK);
		}*/

		float fMX = g_tMonster.tSphere.x - ptMouse.x;
		float fMY = g_tMonster.tSphere.y - ptMouse.y;
		float fMDist = sqrtf(fMX * fMX + fMY * fMY);
		if (g_tMonster.tSphere.r >= fMDist) {
			MessageBox(NULL, L"���� Ŭ��", L"���콺Ŭ��", MB_OK);
		}
	}

	RECT rcWindow;
	GetClientRect(g_hWnd, &rcWindow);
	SetRect(&rcWindow, 0, 0, 800, 600);

	/*if (g_tPlayerRC.l < 0) {
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
	}*/
	// ���� �̵� 
	g_tMonster.tSphere.y += g_tMonster.fSpeed * g_fDeltatime *
		fTimeScale * g_tMonster.iDir;
    //g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltatime *
	//	fTimeScale * g_tMonster.iDir;

	if (g_tMonster.tSphere.y + g_tMonster.tSphere.r >= 600) {
		g_tMonster.iDir = -1;
		g_tMonster.tSphere.y = 550;
	}

	if (g_tMonster.tSphere.y - g_tMonster.tSphere.r <= 0) {
		g_tMonster.iDir = 1;
		g_tMonster.tSphere.y = 50;
	}
	// ���� �Ѿ� �߻� ����
	g_tMonster.fTime += g_fDeltatime;

	if (g_tMonster.fTime >= g_tMonster.fLimitTime) {
		g_tMonster.fTime -= g_tMonster.fLimitTime;

		BULLET tBullet = {};
		tBullet.tSphere.x = g_tMonster.tSphere.x - g_tMonster.tSphere.r-15.f;
		tBullet.tSphere.y = g_tMonster.tSphere.y;
		tBullet.tSphere.r = 5.f;

		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 800.f;

		g_MonsterBulletList.push_back(tBullet);
	}

	

	// �÷��̾� �Ѿ� �̵�
	list<BULLET>::iterator iter;
	list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

	fSpeed = 600.f * g_fDeltatime * fTimeScale;
	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;) {

		(*iter).tSphere.x += cosf((*iter).fAngle) * fSpeed;
		(*iter).tSphere.y += sinf((*iter).fAngle) * fSpeed;

		(*iter).fDist += fSpeed;

		float fX = (*iter).tSphere.x - g_tMonster.tSphere.x;
		float fY = (*iter).tSphere.y - g_tMonster.tSphere.y;
		float fDist = sqrtf(fX*fX + fY*fY);

		if (fDist <= (*iter).tSphere.r + g_tMonster.tSphere.r) {
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		else if ((*iter).fDist >= (*iter).fLimitDist) {
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		else if ((*iter).tSphere.x - (*iter).tSphere.r >= 800) {
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}

		// �÷��̾� �Ѿ� �� ���� �浹ó��
		/*else if (g_tMonster.tRC.l <= (*iter).rc.r && g_tMonster.tRC.r >= (*iter).rc.l&&
			g_tMonster.tRC.t <= (*iter).rc.b&&g_tMonster.tRC.b >= (*iter).rc.t) {
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		*/
		else
			iter++;
	} 
	// ���� �Ѿ� �̵�
	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd;) {
		(*iter).tSphere.x -= fSpeed;

		(*iter).fDist += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist) {
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}

		else if ((*iter).tSphere.x + (*iter).tSphere.r <= 0) {
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}

		/*else if (g_tPlayerRC.l <= (*iter).rc.r && g_tPlayerRC.r >= (*iter).rc.l&&
			g_tPlayerRC.t <= (*iter).rc.b&&g_tPlayerRC.b >= (*iter).rc.t) {
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		*/
		else 
			iter++;		
	}

	// ���
	// Rectangle(g_hDC, 0, 0, 800, 600);

	Ellipse(g_hDC, g_tPlayer.x - g_tPlayer.r, g_tPlayer.y - g_tPlayer.r, g_tPlayer.x + g_tPlayer.r, g_tPlayer.y + g_tPlayer.r);
	Ellipse(g_hDC, g_tMonster.tSphere.x - g_tMonster.tSphere.r, g_tMonster.tSphere.y - g_tMonster.tSphere.r,
		g_tMonster.tSphere.x + g_tMonster.tSphere.r ,g_tMonster.tSphere.y + g_tMonster.tSphere.r);

	MoveToEx(g_hDC, g_tPlayer.x, g_tPlayer.y, NULL);
	LineTo(g_hDC, g_tGunPos.x, g_tGunPos.y);

	// �÷��̾� �Ѿ� ���
	iterEnd = g_PlayerBulletList.end();
	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter) {
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r, (*iter).tSphere.y - (*iter).tSphere.r, 
			(*iter).tSphere.x + (*iter).tSphere.r, (*iter).tSphere.y + (*iter).tSphere.r);
	}

	// ���� �Ѿ� ���
	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd; ++iter) {
		Ellipse(g_hDC, (*iter).tSphere.x - (*iter).tSphere.r, (*iter).tSphere.y - (*iter).tSphere.r,
			(*iter).tSphere.x + (*iter).tSphere.r, (*iter).tSphere.y + (*iter).tSphere.r);
	}
}

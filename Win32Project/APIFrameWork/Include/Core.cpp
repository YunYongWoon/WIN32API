#include "Core.h"
#include "Scene\SceneManager.h"
#include "Core\Timer.h"

DEFINITION_SINGLE(CCore)
bool CCore::m_bLoop = true;

CCore::CCore() {
}


CCore::~CCore() {
	DESTROY_SINGLE(CSceneManager);
}

bool CCore::Init(HINSTANCE hInst) {
	this->m_hInst = hInst;
	MyRegisterClass();

	// �ػ� ����
	m_tRS.iW = 1280;
	m_tRS.iH = 720;

	Create();

	// Ÿ�̸� �ʱ�ȭ
	if (!GET_SINGLE(CTimer)->Init())
		return false;

	// �������� �ʱ�ȭ
	DESTROY_SINGLE(CTimer);
	if (!GET_SINGLE(CSceneManager)->Init())
		return false;

	return true;
}

int CCore::Run() {
	MSG msg;

	// �⺻ �޽��� �����Դϴ�.
	while (m_bLoop) {
		// PeekMessage�� �޽����� �޽���ť�� ��� �ٷ� ���� ���´�.
		// �޽����� ���� ��� true, ���� ��� false�� �ȴ�.
		// �޽����� ���� �ð��� �������� ����Ÿ���̴�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// �����찡 ����Ÿ���� ���
		else {
		}
	}

	return (int)msg.wParam;
	
}

void CCore::Logic() {
	// Ÿ�̸� ���� 
	GET_SINGLE(CTimer)->Update();

	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
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
	wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_WIN32PROJECT);		//�޴�
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

	// ���� ������ Ÿ��Ʋ�ٳ� �޴��� ������ �������� ũ�⸦
	// �����ش�.

	RECT rc = { 0,0,m_tRS.iW,m_tRS.iH };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);


	// ������ ������ ũ��� ������ Ŭ���̾�Ʈ ������ ũ�⸦ 
	// ���ϴ� ũ��� ������� �Ѵ�.
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
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

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


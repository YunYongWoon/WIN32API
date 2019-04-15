#include "MapEditScene.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"
#include "../Collider/ColliderPixel.h"
#include "../Collider/ColliderRect.h"
#include "../Core.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "../Core/Input.h"
#include "../Resources/ResourceManager.h"
#include "../Resources/Texture.h"
#include "../resource.h"@
#include "../Core/PathManager.h"

wchar_t CMapEditScene::m_strText[MAX_PATH] = {};

CMapEditScene::CMapEditScene() {
	m_eTem = TEM_TEXTURE;
}


CMapEditScene::~CMapEditScene() {
	Safe_Release_VecList(m_vecTileTex);
	SAFE_RELEASE(m_pStage);
}

bool CMapEditScene::Init() {
	GET_SINGLE(CCamera)->SetWorldResolution(1920, 1080);

	CTexture* pNoneTex = GET_SINGLE(CResourceManager)->LoadTexture("TileNone", L"Tile/NoneTile.bmp");
	pNoneTex->SetColorKey(255, 0, 255);
	SAFE_RELEASE(pNoneTex);

	CTexture* pNoMoveTex = GET_SINGLE(CResourceManager)->LoadTexture("TileNoMove", L"Tile/NoMoveTile.bmp");
	pNoMoveTex->SetColorKey(255, 0, 255);
	SAFE_RELEASE(pNoMoveTex);

	CLayer* pStageLayer = FindLayer("Stage");

	m_pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);

	m_pStage->CreateTile(40, 40, 48, 27, "BaseTile", L"Tile/Tile2.bmp");
	
	CTexture* pTex = GET_SINGLE(CResourceManager)->FindTexture("BaxeTile");
	m_vecTileTex.push_back(pTex);

	pTex = GET_SINGLE(CResourceManager)->LoadTexture("Tile1", L"Tile/Tile2.bmp");
	m_vecTileTex.push_back(pTex);

	pTex = GET_SINGLE(CResourceManager)->LoadTexture("Tile2", L"Tile/Tile1.bmp");
	m_vecTileTex.push_back(pTex);

	m_iEditTileTex = 0;
	m_eEditOption = TO_NONE;

	GET_SINGLE(CInput)->AddKey("Save", 'S', VK_CONTROL);
	GET_SINGLE(CInput)->AddKey("Load", 'O', VK_CONTROL);

	return true;
}

void CMapEditScene::Input(float fDeltaTime) {
	CScene::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(0.f, -300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(0.f, 300.f * fDeltaTime);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(-300.f * fDeltaTime, 0.f);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		GET_SINGLE(CCamera)->Scroll(300.f * fDeltaTime, 0.f);
	}

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		m_eTem = TEM_TEXTURE;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000) {
		m_eTem = TEM_OPTION;
	}

	if (GetAsyncKeyState('1') & 0x8000) {
		switch (m_eTem) {
		case TEM_TEXTURE:
			m_iEditTileTex = 0;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NONE;
			break;
		}
	}

	if (GetAsyncKeyState('2') & 0x8000) {
		switch (m_eTem) {
		case TEM_TEXTURE:
			m_iEditTileTex = 1;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		}
	}

	if (GetAsyncKeyState('3') & 0x8000) {
		switch (m_eTem) {
		case TEM_TEXTURE:
			m_iEditTileTex = 2;
			break;
		case TEM_OPTION:
			m_eEditOption = TO_NOMOVE;
			break;
		}
	}

	if (KEYPRESS("MouseLButton")) {
		POSITION tMouseWorldPos = MOUSEWORLDPOS;

		switch (m_eTem) {
		case TEM_TEXTURE:
			m_pStage->ChangeTileTexture(tMouseWorldPos, m_vecTileTex[m_iEditTileTex]);
			break;
		case TEM_OPTION:
			m_pStage->ChangeTileOption(tMouseWorldPos, m_eEditOption);
			break;
		}
	}

	if (KEYPRESS("MouseRButton")) {

	}

	if (KEYDOWN("Save")) {
		ShowCursor(TRUE);
		DialogBox(WINDOWINSTANCE, MAKEINTRESOURCE(IDD_DIALOG1),
			WINDOWHANDLE,CMapEditScene::DlgProc);

		ShowCursor(FALSE);

		// 파일명을 이용하여 저장
		char strFileName[MAX_PATH] = {};

		WideCharToMultiByte(CP_ACP, 0, m_strText, -1, strFileName,
			lstrlen(m_strText), 0, 0);

		const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(DATA_PATH);

		string strFullPath;

		if (pPath)
			strFullPath = pPath;
		strFullPath += strFileName;

		FILE* pFile = NULL;

		fopen_s(&pFile, strFullPath.c_str(), "wb");

		if (pFile) {
			fclose(pFile);
		}
	}

	if (KEYDOWN("Load")) {

	}
}

INT_PTR CMapEditScene::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			// Edit Box에서 문자열을 얻어온다.
			memset(m_strText, 0, sizeof(wchar_t)*MAX_PATH);
			GetDlgItemText(hWnd, IDC_EDIT2, m_strText, MAX_PATH);
		case IDCANCEL:
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

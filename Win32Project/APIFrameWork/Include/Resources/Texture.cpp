#include "Texture.h"
#include "../Core/PathManager.h"


CTexture::CTexture() : m_hMemDC(NULL) {
}


CTexture::~CTexture() {
	// 기존에 저장되어있던 도구로 다시 지정해준다.
	SelectObject(m_hMemDC, m_hOldBitmap);

	// Bitmap 지워주기
	DeleteObject(m_hBitmap);

	// DC를 지워준다.
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, 
	const string & strKey, const wchar_t * pFileName, 
	const string & strPathKey) {

	// 메모리 DC를 만들어준다.
	m_hMemDC = CreateCompatibleDC(hDC);

	// 전체 경로를 만들어준다.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);
	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 위에서 만들어준 비트맵 도구를 DC에 지정한다.
	// 지정 시 반환값은 DC에 기본으로 저장되어 있던 도구가 반환된다.

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}

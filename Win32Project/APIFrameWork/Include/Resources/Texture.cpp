#include "Texture.h"
#include "../Core/PathManager.h"
#include "ResourceManager.h"

CTexture::CTexture() :
	m_hMemDC(NULL), 
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255)) {

}


CTexture::~CTexture() {
	// 기존에 저장되어있던 도구로 다시 지정해준다.
	SelectObject(m_hMemDC, m_hOldBitmap);

	// Bitmap 지워주기
	DeleteObject(m_hBitmap);

	// DC를 지워준다.
	DeleteDC(m_hMemDC);
}

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b) {
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void CTexture::SetColorKey(COLORREF ColorKey) {
	m_ColorKey = ColorKey;
	m_bColorKeyEnable = true;
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC,
	const string & strKey, const wchar_t * pFileName, 
	const string & strPathKey) {
	m_strFileName = pFileName;
	m_strKey = strKey;
	m_strPathKey = strPathKey;

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

void CTexture::SaveFromPath(const char * pFileName, const string & strPathKey) {
}

void CTexture::Save(FILE * pFile) {
	// key의 길이 저장
	int iLength = m_strKey.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strKey.c_str(), 1, iLength, pFile);

	// FileName 저장
	iLength = m_strFileName.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 2, iLength, pFile);

	// PathKey 저장
	iLength = m_strPathKey.length();
	fwrite(&m_strPathKey, 4, 1, pFile);
	fwrite(m_strPathKey.c_str(), 1, iLength, pFile);

	// ColorKey
	fwrite(&m_ColorKey, 1, 1, pFile);
	fwrite(&m_bColorKeyEnable, sizeof(COLORREF), 1, pFile);
}

void CTexture::LoadFromPath(const char * pFileName, const string & strPathKey) {
}

void CTexture::Load(FILE * pFile) {
	int iLength = 0;

	char strKey[MAX_PATH] = {};
	char strPathKey[MAX_PATH] = {};
	wchar_t strFileName[MAX_PATH] = {};

	// strkey 불러오기
	fread(&iLength, 4, 1, pFile);
	fread(strKey, 1, iLength, pFile);
	strKey[iLength] = 0;

	// FileName 불러오기
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strFileName, 2, iLength, pFile);
	strFileName[iLength] = 0;

	// PathKey 불러오기
	iLength = 0;
	fread(&m_strPathKey, 4, 1, pFile);
	fread(strPathKey, 1, iLength, pFile);
	strPathKey[iLength] = 0;

	GET_SINGLE(CResourceManager)->LoadTexture(strKey, strFileName, strPathKey);
}

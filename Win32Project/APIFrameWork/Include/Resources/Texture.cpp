#include "Texture.h"
#include "../Core/PathManager.h"
#include "ResourceManager.h"

CTexture::CTexture() :
	m_hMemDC(NULL), 
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255)) {

}


CTexture::~CTexture() {
	// ������ ����Ǿ��ִ� ������ �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBitmap);

	// Bitmap �����ֱ�
	DeleteObject(m_hBitmap);

	// DC�� �����ش�.
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

	// �޸� DC�� ������ش�.
	m_hMemDC = CreateCompatibleDC(hDC);

	// ��ü ��θ� ������ش�.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);
	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// ������ ������� ��Ʈ�� ������ DC�� �����Ѵ�.
	// ���� �� ��ȯ���� DC�� �⺻���� ����Ǿ� �ִ� ������ ��ȯ�ȴ�.

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);

	return true;
}

void CTexture::SaveFromPath(const char * pFileName, const string & strPathKey) {
}

void CTexture::Save(FILE * pFile) {
	// key�� ���� ����
	int iLength = m_strKey.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strKey.c_str(), 1, iLength, pFile);

	// FileName ����
	iLength = m_strFileName.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 2, iLength, pFile);

	// PathKey ����
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

	// strkey �ҷ�����
	fread(&iLength, 4, 1, pFile);
	fread(strKey, 1, iLength, pFile);
	strKey[iLength] = 0;

	// FileName �ҷ�����
	iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(strFileName, 2, iLength, pFile);
	strFileName[iLength] = 0;

	// PathKey �ҷ�����
	iLength = 0;
	fread(&m_strPathKey, 4, 1, pFile);
	fread(strPathKey, 1, iLength, pFile);
	strPathKey[iLength] = 0;

	GET_SINGLE(CResourceManager)->LoadTexture(strKey, strFileName, strPathKey);
}

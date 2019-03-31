#include "ColliderPixel.h"
#include "ColliderSphere.h"
#include "../Object/Obj.h" 
#include "ColliderRect.h"
#include "../Core/PathManager.h"


CColliderPixel::CColliderPixel() {
	m_eCollType = CT_RECT;
	m_iWidth = 0;
	m_iHeight = 0;
}

CColliderPixel::CColliderPixel(const CColliderPixel & coll) : CCollider(coll) {
	m_iWidth = coll.m_iWidth;
	m_iHeight = coll.m_iHeight;
}


CColliderPixel::~CColliderPixel() {
}

bool CColliderPixel::SetPixelInfo(char * pFileName, const string & strPathKey) {
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultiByte(strPathKey);
	string strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	FILE*  pFile = NULL;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (!pFile)
		return false;

	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	fread(&fh, sizeof(fh), 1, pFile);
	fread(&ih, sizeof(ih), 1, pFile);

	m_iWidth = ih.biWidth;
	m_iHeight = ih.biHeight;

	m_vecPixel.clear();

	m_vecPixel.resize(m_iWidth * m_iHeight);

	fread(&m_vecPixel[0], sizeof(PIXEL), m_vecPixel.size(), pFile);

	PPIXEL pPixelArr = new PIXEL[m_iWidth];

	// 위 아래를 반전시켜준다.
	for (int i = 0; i < m_iHeight / 2; i++) {
		// 현재 인덱스의 픽셀 한 줄을 저장해둔다.
		memcpy(pPixelArr, &m_vecPixel[i * m_iWidth],sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[i * m_iWidth], &m_vecPixel[(m_iHeight - i - 1) * m_iWidth],sizeof(PIXEL) * m_iWidth);
		memcpy(&m_vecPixel[(m_iHeight - i - 1) * m_iWidth], pPixelArr, sizeof(PIXEL) * m_iWidth);
	}

	delete[] pPixelArr;

	fclose(pFile);
	return true;
}

bool CColliderPixel::Init() {
	return true;
}

void CColliderPixel::Input(float fDeltaTime) {
}

int CColliderPixel::Update(float fDeltaTime) {
	return 0;
}

int CColliderPixel::LateUpdate(float fDeltaTime) {
	return 0;
}

bool CColliderPixel::Collision(CCollider * pDest) {
	switch (pDest->GetColliderType()) {
	case CT_RECT:
		return CollisionRectToPixel(((CColliderRect*)pDest)->GetWorldInfo(),
			m_vecPixel, m_iWidth, m_iHeight);
	}
	return false;
}

void CColliderPixel::Render(HDC hDC, float fDeltaTime) {
}

CColliderPixel * CColliderPixel::Clone() {
	return new CColliderPixel(*this);
}

#include "Stage.h"
#include "../Resources/Texture.h"
#include "../Core.h"
#include "../Core/Camera.h"
#include "Tile.h"
#include "../Scene/Layer.h"

CStage::CStage() {
}

CStage::CStage(const CStage & stage) : CStaticObj(stage) {
	m_vecTile.clear();
	for (size_t i = 0; i < stage.m_vecTile.size(); i++) {
		m_vecTile.push_back(stage.m_vecTile[i]->Clone());
	}
}


CStage::~CStage() {
	Safe_Release_VecList(m_vecTile);
}

void CStage::CreateTile(int iNumX, int iNumY, int iSizeX, int iSizeY, 
	const string & strKey, const wchar_t * pFileName, 
	const string & strPathKey) {
	Safe_Release_VecList(m_vecTile);

	m_iTileNumX = iNumX;
	m_iTileNumY = iNumY;
	m_iTileSizeX = iSizeX;
	m_iTileSizeY = iSizeY;

	for (int i = 0; i < iNumY; i++) {
		for (int j = 0; j < iNumX; j++) {
			CTile* pTile = CObj::CreateObj<CTile>("Tile");

			pTile->SetSize(iSizeX, iSizeY);
			pTile->SetPos(j*iSizeX, i*iSizeY);

			pTile->SetTexture(strKey, pFileName, strPathKey);

			m_vecTile.push_back(pTile);

			SAFE_RELEASE(pTile);
		}
	}
}

bool CStage::Init() {
	SetPos(0.f, 0.f);
	SetSize(1920.f, 1080.f);
	SetPivot(0.f, 0.f);

	SetTexture("Stage1", L"Stage1.bmp");

	return true;
}

void CStage::Input(float fDeltaTime) {
	CStaticObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime) {
	CStaticObj::Update(fDeltaTime);
	return 0;
}

int CStage::LateUpdate(float fDeltaTime) {
	CStaticObj::LateUpdate(fDeltaTime);
	return 0;
}

void CStage::Collision(float fDeltaTime) {
	CStaticObj::Collision(fDeltaTime);
}

void CStage::Render(HDC hDC, float fDeltaTime) {
	CStaticObj::Render(hDC, fDeltaTime);
	if (m_pTexture) {
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();
	
		BitBlt(hDC, tPos.x, tPos.y, GETRESOLUTION.iW, GETRESOLUTION.iH, m_pTexture->GetDC(),
			tCamPos.x, tCamPos.y, SRCCOPY);
	}
	for (size_t i = 0; i < m_vecTile.size(); i++) {
		m_vecTile[i]->Render(hDC, fDeltaTime);
	}
}

CStage * CStage::Clone() {
	return new CStage(*this);
}

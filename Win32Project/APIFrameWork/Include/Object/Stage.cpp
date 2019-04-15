#include "Stage.h"
#include "../Resources/Texture.h"
#include "../Core.h"
#include "../Core/Camera.h"
#include "Tile.h"
#include "../Scene/Layer.h"
#include "../Core/PathManager.h"

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

	// Grid를 그린다.
	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

	for (int i = 1; i < m_iTileNumY; i++) {
		// 가로줄을 그린다.
		MoveToEx(hDC, 0.f, i*m_iTileSizeY - tCamPos.y, NULL);
		LineTo(hDC, m_iTileNumX*m_iTileSizeX, i*m_iTileSizeY - tCamPos.y);

	}

	for (int j = 0; j < m_iTileNumX; j++) {
		// 세로줄을 그린다.
		MoveToEx(hDC, j*m_iTileSizeX - tCamPos.x, 0, NULL);
		LineTo(hDC, j*m_iTileSizeX - tCamPos.x, m_iTileNumY*m_iTileSizeY);
	}

}

CStage * CStage::Clone() {
	return new CStage(*this);
}

void CStage::Save(FILE * pFile) {
	CStaticObj::Save(pFile);

	// 스테이지 정보 저장
	fwrite(&m_iTileNumX, 4, 1, pFile);
	fwrite(&m_iTileNumY, 4, 1, pFile);
	fwrite(&m_iTileSizeX, 4, 1, pFile);
	fwrite(&m_iTileSizeX, 4, 1, pFile);

	for (size_t i = 0; i < m_vecTile.size(); i++) {
		m_vecTile[i]->Save(pFile);
	}
}


void CStage::Load(FILE * pFile) {
	CStaticObj::Load(pFile);

	CStaticObj::Save(pFile);

	// 스테이지 정보 저장
	fread(&m_iTileNumX, 4, 1, pFile);
	fread(&m_iTileNumY, 4, 1, pFile);
	fread(&m_iTileSizeX, 4, 1, pFile);
	fread(&m_iTileSizeX, 4, 1, pFile);

	Safe_Release_VecList(m_vecTile);

	for (int i = 0; i < m_iTileNumX * m_iTileNumY; i++) {
		CTile* pTile = CObj::CreateObj<CTile>("Tile");

		pTile->Load(pFile);

		m_vecTile.push_back(pTile);

		SAFE_RELEASE(pTile);
	}
}

void CStage::ChangeTileTexture(const POSITION & tPos, CTexture * pTexture) {
	int iIndex = GetTileIndex(tPos);

	if (iIndex == -1)
		return;

	m_vecTile[iIndex]->SetTexture(pTexture);
}

void CStage::ChangeTileOption(const POSITION & tPos, TILE_OPTION eOption) {
	int iIndex = GetTileIndex(tPos);

	if (iIndex == -1)
		return;

	m_vecTile[iIndex]->SetTileOption(eOption);
}

int CStage::GetTileIndex(const POSITION & tPos) {
	return GetTileIndex(tPos.x, tPos.y);
}

int CStage::GetTileIndex(float x, float y) {
	int idxX = (int)x / m_iTileSizeX;
	int idxY = (int)y / m_iTileSizeY;

	if (idxX < 0 || idxX >= m_iTileNumX)
		return -1;

	else if (idxY < 0 || idxY >= m_iTileNumY)
		return -1;

	return idxY * m_iTileNumX + idxX;
}

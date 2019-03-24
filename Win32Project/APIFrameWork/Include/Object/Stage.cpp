#include "Stage.h"
#include "../Resources/Texture.h"
#include "../Core.h"


CStage::CStage() {
}

CStage::CStage(const CStage & stage) : CStaticObj(stage) {

}


CStage::~CStage() {
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
	
		BitBlt(hDC, tPos.x, tPos.y, GETRESOLUTION.iW, GETRESOLUTION.iH, m_pTexture->GetDC(), 0, 0, SRCCOPY);
	}
}

CStage * CStage::Clone() {
	return new CStage(*this);
}

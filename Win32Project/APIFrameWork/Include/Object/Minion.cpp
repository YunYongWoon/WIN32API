#include "Minion.h"
#include "../Core.h"


CMinion::CMinion() : m_fFireTime(0.f), m_fFireTimeLimit(1.1f){
}

CMinion::CMinion(const CMinion & minion) : CMoveObj(minion) {
	m_eDir = minion.m_eDir;
	m_fFireTime = minion.m_fFireTime;
	m_fFireTimeLimit = minion.m_fFireTimeLimit;
}


CMinion::~CMinion() {
}

bool CMinion::Init() {
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(300.f);

	m_eDir = MD_FRONT;
	return true;
}

int CMinion::Update(float fDeltaTime) {
	CMoveObj::Update(fDeltaTime);

	MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.y + m_tSize.y >= GETRESOLUTION.iH) {
		m_tPos.y = GETRESOLUTION.iH - m_tSize.y;
		m_eDir = MD_BACK;
	}
	else if(m_tPos.y<=0.f){
		m_tPos.y = 0.f;
		m_eDir = MD_FRONT;
	}

	m_fFireTime += fDeltaTime;
	if (m_fFireTime>=m_fFireTimeLimit) {
		m_fFireTime -= m_fFireTimeLimit;
		Fire();
	}

	return 0;
}

int CMinion::LateUpdate(float fDeltaTime) {
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMinion::Collision(float fDeltaTime) {
	CMoveObj::Collision(fDeltaTime);
}

void CMinion::Render(HDC hDC, float fDeltaTime) {
	CMoveObj::Render(hDC, fDeltaTime);
	Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

CMinion * CMinion::Clone() {
	return new CMinion(*this);
}

void CMinion::Fire() {
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "MinionBullet", m_pLayer);

	((CMoveObj*)pBullet)->SetAngle(PI);

	pBullet->SetPos(m_tPos.x - pBullet->GetSize().x,
		(m_tPos.y + m_tPos.y + m_tSize.y) / 2.f - pBullet->GetSize().y / 2.f);

	SAFE_RELEASE(pBullet);
}

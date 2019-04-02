#include "Player.h"
#include "../Core/Input.h"
#include "Bullet.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Camera.h"

CPlayer::CPlayer() {
}

CPlayer::CPlayer(const CPlayer & player) : CMoveObj(player){

}


CPlayer::~CPlayer() {
}

bool CPlayer::Init() {
	SetPos(50.f, 50.f);
	SetSize(100.f, 100.f);
	SetSpeed(400.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", L"HoTS.bmp");

	CColliderRect* pRC = AddCollider<CColliderRect>("Player");

	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	pRC->AddCollisionFunction(CS_ENTER, this,
		&CPlayer::Hit);
	pRC->AddCollisionFunction(CS_STAY, this,
		&CPlayer::HitStay);

	SAFE_RELEASE(pRC);

	m_iHP = 0;

	// 중력 적용
	SetPhysics(true);

	// 점프할 힘을 적용
	SetForce(200.f);


	return true;
}
void CPlayer::Input(float fDeltaTime) {
	CMoveObj::Input(fDeltaTime);

	if (KEYPRESS("MoveUp")) {
		Jump();
	}
	if (KEYPRESS("MoveBottom")) {
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}
	if (KEYPRESS("MoveLeft")) {
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}
	if (KEYPRESS("MoveRight")) {
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (KEYDOWN("Fire")) {
		Fire();
	}
}

int CPlayer::Update(float fDeltaTime) {
	CMoveObj::Update(fDeltaTime);
	return 0;
}

int CPlayer::LateUpdate(float fDeltaTime) {
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CPlayer::Collision(float fDeltaTime) {
	CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime) {
	CMoveObj::Render(hDC, fDeltaTime);
	wchar_t strHP[32] = {};
	wsprintf(strHP, L"Count : %d", m_iHP);
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	tPos -= GET_SINGLE(CCamera)->GetPos();

	TextOut(hDC, tPos.x, tPos.y, strHP, lstrlen(strHP));

	//Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

CPlayer * CPlayer::Clone() {
	return new CPlayer(*this);
}

void CPlayer::Fire() {
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet",m_pLayer);

	pBullet->AddCollisionFunction("Bullet", CS_ENTER, (CBullet*)pBullet, &CBullet::Hit);

	// 오른쪽 가운데를 구한다.
	POSITION tPos;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = m_tPos.y + (0.5f - m_tPivot.y) * m_tSize.y;

	pBullet->SetPos(tPos);

	SAFE_RELEASE(pBullet);
}

void CPlayer::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime) {
	if(pDest->GetObj()->GetTag() == "MinionBullet")
		m_iHP += 1;

	else if (pDest->GetTag() == "StageColl") {
		ClearGravity();
		JumpEnd();
	}
}

void CPlayer::HitStay(CCollider * pSrc, CCollider * pDest, float fDeltaTime) {
	if (pDest->GetTag() == "StageColl") {
		ClearGravity();
		JumpEnd();
	}
}

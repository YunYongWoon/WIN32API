#include "Player.h"

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

	SetTexture("player", L"HoTS.bmp");

	return true;
}
void CPlayer::Input(float fDeltaTime) {
	CMoveObj::Input(fDeltaTime);

	if (GetAsyncKeyState('W') & 0x8000) {
		MoveYFromSpeed(fDeltaTime, MD_BACK);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		MoveYFromSpeed(fDeltaTime, MD_FRONT);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		MoveXFromSpeed(fDeltaTime, MD_BACK);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		MoveXFromSpeed(fDeltaTime, MD_FRONT);
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
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
	//Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

CPlayer * CPlayer::Clone() {
	return new CPlayer(*this);
}

void CPlayer::Fire() {
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet",m_pLayer);

	// 오른쪽 가운데를 구한다.
	POSITION tPos;
	tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
	tPos.y = m_tPos.y + (0.5f - m_tPivot.y) * m_tSize.y;

	pBullet->SetPos(tPos);

	SAFE_RELEASE(pBullet);
}

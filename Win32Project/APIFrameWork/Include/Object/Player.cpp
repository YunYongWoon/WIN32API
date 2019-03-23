#include "Player.h"

CPlayer::CPlayer() {
}

CPlayer::CPlayer(const CPlayer & player) : CMoveObj(player){

}


CPlayer::~CPlayer() {
}

bool CPlayer::Init() {
	SetPos(100.f, 100.f);
	SetSize(100.f, 100.f);
<<<<<<< HEAD
	SetSpeed(400.f);
=======
>>>>>>> d63d3f72a23ca8c2a58faf79d4ede9e5a09c6f64
	return true;
}

void CPlayer::Input(float fDeltaTime) {
	CMoveObj::Input(fDeltaTime);
<<<<<<< HEAD

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
=======
>>>>>>> d63d3f72a23ca8c2a58faf79d4ede9e5a09c6f64
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
	Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

#include "Mouse.h"
#include "../Core.h"
#include "../Collider/ColliderPoint.h"

CMouse::CMouse() {
}

CMouse::CMouse(const CMouse & mouse) : CUI(mouse) {
}


CMouse::~CMouse() {
}

bool CMouse::Init() {
	POINT pt;

	// 스크린 좌표 기준으로 나온다.
	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	ShowCursor(false);

	m_tPos = pt;

	CColliderPoint* pColl = AddCollider<CColliderPoint>("Mouse");

	SAFE_RELEASE(pColl);

	return true;
}

void CMouse::Input(float fDeltaTime) {
	CUI::Input(fDeltaTime);
}

int CMouse::Update(float fDeltaTime) {
	CUI::Update(fDeltaTime);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	m_tMove.x = pt.x - m_tPos.x;
	m_tMove.y = pt.y - m_tPos.y;

	m_tPos = pt;

	return 0;
}

int CMouse::LateUpdate(float fDeltaTime) {
	CUI::LateUpdate(fDeltaTime);
	return 0;
}

void CMouse::Collision(float fDeltaTime) {
	CUI::Collision(fDeltaTime);
}

void CMouse::Render(HDC hDC, float fDeltaTime) {
	CUI::Render(hDC, fDeltaTime);
}

CMouse * CMouse::Clone() {
	return new CMouse(*this);
}

void CMouse::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime) {
}

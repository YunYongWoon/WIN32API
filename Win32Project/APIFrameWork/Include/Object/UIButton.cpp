#include "UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Input.h"


CUIButton::CUIButton() :
	m_bEnableCallback(false), m_eState(BS_NONE) {
}

CUIButton::CUIButton(const CUIButton & ui) : CUI(ui) {
	m_bEnableCallback = false;
	m_eState = BS_NONE;
}


CUIButton::~CUIButton() {
}

bool CUIButton::Init() {
	CColliderRect* pColl = AddCollider<CColliderRect>("ButtonBody");

	SAFE_RELEASE(pColl);
	return true;
}

void CUIButton::Input(float fDeltaTime) {
	CUI::Input(fDeltaTime);
}

int CUIButton::Update(float fDeltaTime) {
	CUI::Update(fDeltaTime);
	return 0;
}

int CUIButton::LateUpdate(float fDeltaTime) {
	CUI::LateUpdate(fDeltaTime);

	if (m_eState != BS_NONE) {
		if (KEYPRESS("MouseLButton")) {
			m_eState = BS_CLICK;
			SetImageOffset(m_tSize.x * 2.f, 0.f);
		}
	}

	if (m_eState == BS_CLICK && KEYUP("MouseLButton")) {
		m_eState = BS_MOUSEON;
		SetImageOffset(m_tSize.x, 0.f);
		if (m_bEnableCallback)
			m_ButtonCallback(fDeltaTime);
	}

	return 0;
}

void CUIButton::Collision(float fDeltaTime) {
	CUI::Collision(fDeltaTime);
}

void CUIButton::Render(HDC hDC, float fDeltaTime) {
	CUI::Render(hDC, fDeltaTime);
}

CUIButton * CUIButton::Clone() {
	return new CUIButton(*this);
}

void CUIButton::MouseOn(CCollider * pSrc, CCollider * pDest, float fDeltaTime) {
	if (pDest->GetTag() == "Mouse") {
		m_eState = BS_MOUSEON;
		SetImageOffset(m_tSize.x, 0.f);
	}
}

void CUIButton::MouseOut(CCollider * pSrc, CCollider * pDest, float fDeltaTime) {
	if (pDest->GetTag() == "Mouse") {
		m_eState = BS_NONE;
		SetImageOffset(0.f, 0.f);
	}
}

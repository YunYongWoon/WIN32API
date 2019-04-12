#include "UIButton.h"
#include "../Collider/ColliderRect.h"
#include "../Core/Input.h"


CUIButton::CUIButton() {
}

CUIButton::CUIButton(const CUIButton & ui) : CUI(ui) {
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

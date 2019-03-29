#include "ColliderRect.h"



CColliderRect::CColliderRect() {
	m_eCollType = CT_RECT;
}

CColliderRect::CColliderRect(const CColliderRect & coll) : CCollider(coll) {
	
}


CColliderRect::~CColliderRect() {
}

bool CColliderRect::Init() {
	return true;
}

void CColliderRect::Input(float fDeltaTime) {
}

int CColliderRect::Update(float fDeltaTime) {
	return 0;
}

int CColliderRect::LateUpdate(float fDeltaTime) {
	return 0;
}

void CColliderRect::Collision(float fDeltaTime) {
}

void CColliderRect::Render(HDC hDC, float fDeltaTime) {
}

CColliderRect * CColliderRect::Clone() {
	return new CColliderRect(*this);
}

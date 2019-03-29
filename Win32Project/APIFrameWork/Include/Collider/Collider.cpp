#include "Collider.h"



CCollider::CCollider() {
}

CCollider::CCollider(const CCollider & coll) {
	*this = coll;
}

CCollider::~CCollider() {
}

void CCollider::Input(float fDeltaTime) {
}

int CCollider::Update(float fDeltaTime) {
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime) {
	return 0;
}

void CCollider::Collision(float fDeltaTime) {
}

void CCollider::Render(HDC hDC, float fDeltaTime) {
}

#include "ColliderPixel.h"
#include "ColliderSphere.h"
#include "../Object/Obj.h" 
#include "ColliderRect.h"
#include "../Core/PathManager.h"


CColliderPixel::CColliderPixel() {
	m_eCollType = CT_RECT;
}

CColliderPixel::CColliderPixel(const CColliderPixel & coll) : CCollider(coll) {
}


CColliderPixel::~CColliderPixel() {
}

bool CColliderPixel::SetPixelInfo(char * pFileName, const string & strPath) {
	return false;
}

bool CColliderPixel::Init() {
	return true;
}

void CColliderPixel::Input(float fDeltaTime) {
}

int CColliderPixel::Update(float fDeltaTime) {
	return 0;
}

int CColliderPixel::LateUpdate(float fDeltaTime) {
	return 0;
}

bool CColliderPixel::Collision(CCollider * pDest) {
	return false;
}

void CColliderPixel::Render(HDC hDC, float fDeltaTime) {
}

CColliderPixel * CColliderPixel::Clone() {
	return new CColliderPixel(*this);
}

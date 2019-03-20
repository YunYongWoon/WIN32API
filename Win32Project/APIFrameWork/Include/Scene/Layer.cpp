#include "Layer.h"
#include "../Object/Obj.h"

CLayer::CLayer() : 
	m_iZOrder(0),
	m_strTag(""),
	m_pScene(NULL) {
}

CLayer::~CLayer() {
	Safe_Release_VecList(m_ObjList);
}

void CLayer::Input(float fDeltaTime) {
}

int CLayer::Update(float fDeltaTime) {
	return 0;
}

int CLayer::LateUpdate(float fDeltaTime) {
	return 0;
}

void CLayer::Collision(float fDeltaTime) {
}

void CLayer::Render(HDC hDC, float fDeltaTime) {
}

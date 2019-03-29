#include "CollisionManager.h"
#include "../Object/Obj.h"
#include "Collider.h"

DEFINITION_SINGLE(CCollisionManager)


CCollisionManager::CCollisionManager() {
}


CCollisionManager::~CCollisionManager() {
}

void CCollisionManager::AddObject(CObj * pObj) {
	if (pObj->CheckCollider()) {
		m_CollisionList.push_back(pObj);
	}
}

void CCollisionManager::Collision(float fDeltaTime) {
	if (m_CollisionList.size() < 2) {
		m_CollisionList.clear();
		return;
	}
	// 오브젝트간 충돌처리를 한다.
	m_CollisionList.clear();
}

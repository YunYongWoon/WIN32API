#include "Collider.h"
#include "../Object/Obj.h"
#include "../Math.h"

CCollider::CCollider() {
}

CCollider::CCollider(const CCollider & coll) {
	*this = coll;
}

CCollider::~CCollider() {
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; iter++) {
		(*iter)->EraseCollisionList(this);		
	}
}

void CCollider::Input(float fDeltaTime) {
}

int CCollider::Update(float fDeltaTime) {
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime) {
	return 0;
}

bool CCollider::Collision(CCollider* pDest) {
	return false;
}

void CCollider::Render(HDC hDC, float fDeltaTime) {
}

bool CCollider::CollisionRectToRect(const RECTANGLE & src, const RECTANGLE & dest) {
	if (src.l > dest.r)
		return false;
	else if (src.r < dest.l)
		return false;
	else if (src.t > dest.b)
		return false;
	else if (src.b < dest.t)
		return false;

	return true;
}

bool CCollider::CollisionRectToSphere(const RECTANGLE & src, const SPHERE & dest) {
	// 원의 중점의 x좌표가 사각형의 가로영역 안에 있는지,
	// 원의 중점의 y좌표가 사각형의 세로 영역 안에 있는지 체크.
	// 둘중 하나라도 맞다면 사각형의 상하좌우 안에 위치.
	if ((src.l <= dest.tCenter.x && dest.tCenter.x <= src.r) ||
		(src.t <= dest.tCenter.y && dest.tCenter.y <= src.b)) {
		RECTANGLE tRC = src;

		tRC.l -= dest.fRadius;
		tRC.t -= dest.fRadius;
		tRC.r += dest.fRadius;
		tRC.b += dest.fRadius;

		if (dest.tCenter.x < tRC.l) {
			return false;
		}
		else if (dest.tCenter.x > tRC.r) {
			return false;
		}
		else if (dest.tCenter.y < tRC.t) {
			return false;
		}
		else if (dest.tCenter.y > tRC.b) {
			return false;
		}

		return true;
	}
	// 사각형의 4개의 점이 하나라도 원 안에 있을 경우 충돌이다.
	POSITION tPos[4];
	tPos[0] = POSITION(src.l, src.t);
	tPos[1] = POSITION(src.r, src.t);
	tPos[2] = POSITION(src.l, src.b);
	tPos[3] = POSITION(src.r, src.b);

	for (int i = 0; i < 4; i++) {
		float fDist = CMath::Distance(tPos[i], dest.tCenter);

		if (fDist <= dest.fRadius)
			return true;
	}

	return false;
}

bool CCollider::CollisionSphereToSphere(const SPHERE & src, const SPHERE & dest) {
	float fDist = CMath::Distance(src.tCenter, dest.tCenter);

	return fDist<=src.fRadius + dest.fRadius;
}

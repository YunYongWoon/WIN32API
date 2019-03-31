#include "Bullet.h"
#include "../Resources/Texture.h"
#include "../Collider/ColliderSphere.h"


CBullet::CBullet() : m_fDist(0.f), m_fLimitDist(500.f) {
}

CBullet::CBullet(const CBullet & bullet) : CMoveObj(bullet) {
	m_fLimitDist = bullet.m_fLimitDist;
	m_fDist = bullet.m_fDist;
}

CBullet::~CBullet() {
}

bool CBullet::Init() {
	SetSpeed(800.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Bullet", L"Timo.bmp");

	m_pTexture->SetColorKey(63, 72, 204);

	CColliderSphere* pSphere = AddCollider<CColliderSphere>("Bullet");

	pSphere->SetSphere(POSITION(0.f,0.f),25.f);

	SAFE_RELEASE(pSphere);
	return true;
}
 
int CBullet::Update(float fDeltaTime) {
	CMoveObj::Update(fDeltaTime);
	MoveAngle(fDeltaTime);

	m_fDist += GetSpeed() * fDeltaTime;

	if (m_fDist >= m_fLimitDist)
		Die();
	
	return 0; 
}

int CBullet::LateUpdate(float fDeltaTime) {
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBullet::Collision(float fDeltaTime) {
	CMoveObj::Collision(fDeltaTime);
}

void CBullet::Render(HDC hDC, float fDeltaTime) {
	CMoveObj::Render(hDC, fDeltaTime);
}

CBullet * CBullet::Clone() {
	return new CBullet(*this);
}

void CBullet::Hit(CCollider * pSrc, CCollider * pDest, float fDeltaTime) {
	if (GetTag() == "PlayerBullet" && pDest->GetTag() == "Minion")
		Die();

	else if (GetTag() == "MinionBullet" && pDest->GetTag() == "Player")
		Die();
}

#include "Bullet.h"



CBullet::CBullet() : m_fDist(0.f), m_fLimitDist(500.f) {
}

CBullet::CBullet(const CBullet & bullet) : CMoveObj(bullet) {
	m_fLimitDist = bullet.m_fLimitDist;
	m_fDist = bullet.m_fDist;
}


CBullet::~CBullet() {
}

bool CBullet::Init() {
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
	Ellipse(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
}

CBullet * CBullet::Clone() {
	return new CBullet(*this);
}

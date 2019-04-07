#pragma once
#include "MoveObj.h"
class CPlayer :
	public CMoveObj {

private:
	friend class CObj;
	friend class CScene;

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

private:
	int m_iHP;
	float m_fTurnSpeed;
	bool m_bAttack;

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPlayer* Clone();

private:
	void Fire();
	

public:
	void Hit(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
	void HitStay(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
};


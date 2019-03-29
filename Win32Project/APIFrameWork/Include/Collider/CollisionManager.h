#pragma once
#include "../Game.h"

class CCollisionManager
{
private:
	list<class CObj*> m_CollisionList;

public:
	void AddObject(class CObj* pObj);
	void Collision(float fDeltaTime);


	DECLARE_SINGLE(CCollisionManager)
};


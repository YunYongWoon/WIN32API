#pragma once
#include "Collider.h"

typedef struct _tagPixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;

}PIXEL,*PPIXEL;

class CColliderPixel :
	public CCollider
{
protected:
	friend class CObj;

protected:
	CColliderPixel();
	CColliderPixel(const CColliderPixel& coll);
	virtual ~CColliderPixel();

public:
	vector<PIXEL> m_vecPixel;

public:
	bool SetPixelInfo(char * pFileName, const string& strPath = TEXTURE_PATH);

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColliderPixel* Clone();
};


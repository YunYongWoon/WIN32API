#include "Obj.h"
#include "../Scene/Layer.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Resources/ResourceManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
#include "../Animation/Animation.h"

list<CObj*> CObj::m_ObjList;

CObj::CObj() : m_pTexture(NULL), m_pAnimation(NULL), m_bisPhysics(false), m_fGravityTime(0.f) {
}

CObj::CObj(const CObj & obj) {
	*this = obj;

	if (obj.m_pAnimation) {
		m_pAnimation = obj.m_pAnimation->Clone();
	}

	m_fGravityTime = 0.f;

	if (m_pTexture)
		m_pTexture->AddRef();

	m_ColliderList.clear();

	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = obj.m_ColliderList.end();

	for (iter = obj.m_ColliderList.begin(); iter != iterEnd; ++iter) {
		CCollider* pColl = (*iter)->Clone();

		pColl->SetObj(this);
		m_ColliderList.push_back(pColl);
	}

}


CObj::~CObj() {
	SAFE_RELEASE(m_pAnimation);
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pTexture);
}

void CObj::AddObj(CObj * pObj) {
	pObj->AddRef();
	m_ObjList.push_back(pObj);
}

CObj * CObj::FindObject(const string & strTag) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;
		}
	}
	return NULL;
}

void CObj::EraseObj(CObj * pObj) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if (*iter == pObj) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj(const string & strTag) {
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; iter++) {
		if ((*iter)->GetTag() == strTag) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
	}
}

void CObj::EraseObj() {
	Safe_Release_VecList(m_ObjList);
}

CAnimation * CObj::CreateAnimation(const string & strTag) {
	SAFE_RELEASE(m_pAnimation);

	m_pAnimation = new CAnimation;

	m_pAnimation->SetTag(strTag);
	m_pAnimation->SetObj(this);

	if (!m_pAnimation->Init()) {
		SAFE_RELEASE(m_pAnimation);
		return NULL;
	}
	m_pAnimation->AddRef();

	return m_pAnimation;
}

bool CObj::AddAnimationClip(const string & strName, ANIMATION_TYPE eType,
	ANIMATION_OPTION eOption, float fAnimationLimitTime, int iFrameMaxX,
	int iFrameMaxY, int iStartX, int iStartY, int iLengthX, int iLengthY,
	float fOptionLimitTime, const string & strTexKey,
	const wchar_t * pFileName, const string & strPathKey) {
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime,
		iFrameMaxX, iFrameMaxY, iStartX, iStartY, iLengthX, iLengthY,
		fOptionLimitTime, strTexKey, pFileName, strPathKey);

	return true;
}

bool CObj::AddAnimationClip(const string& strName, ANIMATION_TYPE eType,
	ANIMATION_OPTION eOption, float fAnimationLimitTime,
	int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
	int iLengthX, int iLengthY, float fOptionLimitTime,
	const string& strTexKey, const vector<wstring>& vecFileName,
	const string& strPathKey) {
	if (!m_pAnimation)
		return false;

	m_pAnimation->AddClip(strName, eType, eOption, fAnimationLimitTime,
		iFrameMaxX, iFrameMaxY, iStartX, iStartY, iLengthX, iLengthY,
		fOptionLimitTime, strTexKey, vecFileName, strPathKey);

	return true;
}

void CObj::SetAnimationClipColorKey(const string & strClip, unsigned char r, unsigned char g, unsigned char b) {
	if (m_pAnimation)
		m_pAnimation->SetClipColorKey(strClip, r, g, b);
}

CCollider * CObj::GetCollider(const string & strTag) {
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; iter++) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;
		}
	}
	return NULL;
}


void CObj::SetTexture(CTexture * pTexture) {
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;

	if (pTexture)
		pTexture->AddRef();
}

void CObj::SetTexture(const string & strKey, const wchar_t * pFileName, const string & strPathKey) {
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strKey, pFileName, strPathKey);

}

void CObj::SetColorKey(unsigned char r, unsigned char g, unsigned char b) {
	m_pTexture->SetColorKey(r, g, b);
}

bool CObj::Init() {
	return true;
}

void CObj::Input(float fDeltaTime) {

}

int CObj::Update(float fDeltaTime) {
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->Update(fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}

		else
			++iter;
	}

	if (m_pAnimation) {
		m_pAnimation->Update(fDeltaTime);
	}

	return 0;
}

int CObj::LateUpdate(float fDeltaTime) {
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}

		else
			++iter;
	}
	return 0;
}

void CObj::Collision(float fDeltaTime) {

}

void CObj::Render(HDC hDC, float fDeltaTime) {
	if (m_pTexture) {
		POSITION tPos = m_tPos - m_tSize * m_tPivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		POSITION tImagePos;

		if (m_pAnimation) {
			PANIMATIONCLIP pClip = m_pAnimation->GetCurrentClip();

			if (pClip->eType == AT_ATLAS) {
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
		}

		tImagePos += m_tImageOffset;

		if (m_pTexture->GetColorKeyEnable()) {
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(),
				tImagePos.x, tImagePos.y, m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else{
			BitBlt(hDC, tPos.x, tPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(), 0, 0, SRCCOPY);
		}	
	}

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}

		else
			++iter;
	}

}

CObj * CObj::CreateCloneObj(const string & strPrototypeKey, 
	const string & strTag, class CLayer* pLayer) {
	CObj* pProto = CScene::FindPrototype(strPrototypeKey);

	if (!pProto)
		return NULL;

	CObj* pObj = pProto->Clone();

	pObj->SetTag(strTag);

	if (pLayer) {
		pLayer->AddObject(pObj);
	}
	AddObj(pObj);

	return pObj;
}



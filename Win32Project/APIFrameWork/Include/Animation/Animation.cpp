#include "Animation.h"
#include "../Resources/Texture.h"
#include "../Resources/ResourceManager.h"
#include "../Object/Obj.h"

CAnimation::CAnimation() {
}

CAnimation::CAnimation(const CAnimation & ani) {
	*this = ani;

	m_mapClip.clear();

	unordered_map<string, PANIMATIONCLIP>::const_iterator iter;
	unordered_map<string, PANIMATIONCLIP>::const_iterator iterEnd = ani.m_mapClip.end();

	for (iter = ani.m_mapClip.begin(); iter != iterEnd; iter++) {
		PANIMATIONCLIP pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;

		for (size_t i = 0; i < pClip->vecTexture.size(); i++) {
			pClip->vecTexture[i]->AddRef();
		}
	}
}


CAnimation::~CAnimation() {
	unordered_map<string, PANIMATIONCLIP>::iterator iter;
	unordered_map<string, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; iter++) {
		for (size_t i = 0; i < iter->second->vecTexture.size(); i++) {
			SAFE_RELEASE(iter->second->vecTexture[i]);
		}
		SAFE_DELETE(iter->second);
	}
	m_mapClip.clear();
}

bool CAnimation::AddClip(const string & strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, 
	float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, 
	int iStartX, int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime, 
	const string & strTexKey, const wchar_t * pFileName, const string & strPathKey) {

	PANIMATIONCLIP pClip = new ANIMATIONCLIP;

	pClip->fAnimationLimitTime = fAnimationLimitTime;
	pClip->iFrameMaxX = iFrameMaxX;
	pClip->iFrameMaxY = iFrameMaxY;
	pClip->iStartX = iStartX;
	pClip->iStartY = iStartY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTime = fOptionLimitTime;

	CTexture* pTex = GET_SINGLE(CResourceManager)->LoadTexture(strTexKey, pFileName, strPathKey);

	pClip->vecTexture.push_back(pTex);

	pClip->fAnimationTime = 0.f;
	pClip->iFrameX = iStartX;
	pClip->iFrameY = iStartY;
	pClip->fOptionTime = 0.f;

	if (m_mapClip.empty()) {
		SetDefaultClip(strName);
		SetCurrentClip(strName);
	}

	m_mapClip.insert(make_pair(strName, pClip));

	return true;

}

void CAnimation::SetCurrentClip(const string & strCurClip) {
	ChangeClip(strCurClip);
}

void CAnimation::SetDefaultClip(const string & strDefaultClip) {
	m_strDefaultClip = strDefaultClip;
}

void CAnimation::ChangeClip(const string & strClip) {
	if (m_strCurClip == strClip)
		return;

	m_strCurClip = strClip;

	if (m_pCurClip) {
		m_pCurClip->iFrameX = m_pCurClip->iStartX;
		m_pCurClip->iFrameY = m_pCurClip->iStartY;
		m_pCurClip->fAnimationTime = 0.f;
		m_pCurClip->fOptionTime = 0.f;
	}

	m_pCurClip = FindClip(strClip);

	if (m_pCurClip->eType == AT_ATLAS)
		m_pObj->SetTexture(m_pCurClip->vecTexture[0]);

	else if (m_pCurClip->eType == AT_FRAME)
		m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFrameX]);
}

PANIMATIONCLIP CAnimation::FindClip(const string & strName) {
	unordered_map<string, PANIMATIONCLIP>::iterator iter = m_mapClip.find(strName);

	if (iter == m_mapClip.end())
		return NULL;

	return iter->second;
}

bool CAnimation::Init() {

	return true;
}

void CAnimation::Update(float fTime) {
}

CAnimation * CAnimation::Clone() {
	return new CAnimation(*this);
}

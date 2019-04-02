#pragma once
#include "../Ref.h"
class CAnimation :
	public CRef
{
private:
	friend class CObj;

private:
	CAnimation();
	CAnimation(const CAnimation& ani);
	~CAnimation();

private:
	unordered_map<string, PANIMATIONCLIP> m_mapClip;

public:
	bool AddClip(const string& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
		float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime, const string& strTexKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);

public:
	bool Init();
	void Update(float fTime);
	CAnimation* Clone();
};

